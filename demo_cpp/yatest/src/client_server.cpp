#include "yatest/client_server.hpp"
#include "yatest/trace.hpp"

namespace yatest {

Server::Server(const Processor& processor, uint16_t port)
    : processor_(processor)
{
    socket_.listenPort(port);
    threads_.push_back(std::thread(&Server::run, this));
}

Server::~Server()
{
    socket_.terminate();
    sync();
}

void Server::sync()
{
    for (auto& t : threads_) t.join();
}

void runSession(const std::shared_ptr<TcpSocket>& client,
                const Server::Processor& processor)
{
    YATEST_DEBUG("new client");
    try
    {
        for (;;)
        {
            auto request = client->read();
            client->write(processor(request));
        }
    }
    catch (const TcpSocket::Disconnect&)
    {
        // client connection has ended up, exit normaly
    }
    catch (const std::exception& ex)
    {
        YATEST_EXCEPTION(ex.what());
    }
    catch (...)
    {
        YATEST_EXCEPTION("unknown");
    }
}

void Server::run()
{
    YATEST_DEBUG("server has started");
    try
    {
        for (;;)
        {
            auto client = std::make_shared<TcpSocket>(socket_.acceptClient());
            threads_.push_back(std::thread(&runSession, client, processor_));
        }
    }
    catch (const TcpSocket::Error&)
    {
        // server socket has been terminated, exit normaly
    }
    catch (const std::exception& ex)
    {
        YATEST_EXCEPTION(ex.what());
    }
    catch (...)
    {
        YATEST_EXCEPTION("unknown");
    }
}

Client::Client(const std::string& host, uint16_t port)
{
    socket_.connectTo(host, port);
}

std::string Client::send(const std::string& message)
{
    socket_.write(message);
    return socket_.read();
}

} // namespace yatest
