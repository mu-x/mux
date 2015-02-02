#ifndef YATEST_CLIENT_SERVER_HPP
#define YATEST_CLIENT_SERVER_HPP

#include "yatest/tcp_socket.hpp" // more stable for c++0x cross compile
                                 // then boost::asio
#include <functional>
#include <vector>
#include <thread>

#include <boost/noncopyable.hpp>

namespace yatest {

const std::string DEFAULT_HOST = "127.0.0.1";
const uint16_t DEFAULT_PORT = 777;

/** The request-answer TCP Server */
class Server
    : boost::noncopyable
{
public:
    typedef std::function<std::string(const std::string&)> Processor;

    /** Starts server on @param port and serves clients in separate threads
     *  by @param processor */
    Server(const Processor& processor, uint16_t port = DEFAULT_PORT);
    ~Server();

    /** Syncs with all inner threads */
    void sync();

private:
    void run();

    Processor processor_;
    TcpSocket socket_;
    std::vector<std::thread> threads_;
};

/** The request-answer TCP Client */
class Client
    : boost::noncopyable
{
public:
    /** Connects to @param host server on @param port */
    Client(const std::string& host = DEFAULT_HOST, uint16_t port = DEFAULT_PORT);

    /** Sends @param message to the server and resurns answer when avaliable */
    std::string send(const std::string& message);

private:
    TcpSocket socket_;
};

} // namespace yatest

#endif // YATEST_CLIENT_SERVER_HPP
