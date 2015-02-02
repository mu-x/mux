#include "yatest/client_server.hpp"
#include "yatest/thread_pool.hpp"
#include "yatest/word_counter.hpp"

#include <iostream>

#include <boost/algorithm/string/join.hpp>

const size_t TOP_COUNT = 10;

int main(int argc, char** argv)
{
    try
    {
        if (argc > 1 && argv[1] == std::string("-h"))
        {
            std::cerr << "Usage: server [WORK_THREAD_COUNT] [PORT]" << std::endl;
            return 1;
        }

        auto threadCount = (argc <= 1) ? yatest::ThreadPool::cpuCoreCount() :
            static_cast<size_t>(std::stoi(argv[1]));
        auto port = (argc <= 2) ? yatest::DEFAULT_PORT :
            static_cast<uint16_t>(std::stoi(argv[2]));

        yatest::ThreadPool threadPool(threadCount);
        yatest::Server::Processor processor =
                [&threadPool](const std::string& path)
        {
            auto wc = yatest::WordCounter::countDirectory(path, threadPool);
            auto top = wc.top(TOP_COUNT);
            return boost::algorithm::join(top, "\n");
        };

        yatest::Server server(processor, port);
        server.sync(); // wait for SIG_KILL or whatever
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Something terrible has happend" << std::endl;
    }
}
