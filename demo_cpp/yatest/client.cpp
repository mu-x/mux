#include "yatest/client_server.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        if (argc <= 1 || argv[1] == std::string("-h"))
        {
            std::cerr << "Usage: client DIRECTORY [HOST] [PORT]" << std::endl;
            return 1;
        }

        std::string message(argv[1]);
        auto host = (argc <= 2) ? yatest::DEFAULT_HOST : std::string(argv[2]);
        auto port = (argc <= 3) ? yatest::DEFAULT_PORT :
            static_cast<uint16_t>(std::stoi(argv[3]));

        yatest::Client client(host, port);
        std::cout << client.send(message) << std::endl;
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
