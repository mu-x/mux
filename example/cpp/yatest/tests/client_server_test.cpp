#include "yatest/client_server.hpp"
#include "yatest/thread_pool.hpp"
#include "yatest/trace.hpp"
#include "yatest/word_counter.hpp"

#include <algorithm>
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

namespace yatest {
namespace test {

std::string reverse(const std::string& message)
{
    std::string copy(message);
    std::reverse(copy.begin(), copy.end());
    return copy;
}

void test(Client& client, const std::string& message)
{
    EXPECT_EQ(client.send(message), reverse(message));
}

TEST(ClientServerTest, Reverse)
{
    Server server(&reverse);
    EXPECT_THROW(Client("ya.ru"), TcpSocket::Error);

    Client client1;
    test(client1, "Hello world");

    Client client2;
    test(client2, "Chuck Norris can pick up a missed call!");

    // client1 again
    test(client1, "When Chuck Norris returns a book to the library,\n"
                  "the librarian pays him late fees.");
}

TEST(ClientServerTest, Real)
{
    ThreadPool threadPool;
    Server server([&threadPool](const std::string& path){
        return WordCounter::countDirectory(path, threadPool).top(1).at(0); });

    Client client;
    EXPECT_EQ(client.send("tests"), "std");
}

} // namespace test
} // namespace yatest

