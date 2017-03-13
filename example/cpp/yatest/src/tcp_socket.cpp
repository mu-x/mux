#include "yatest/tcp_socket.hpp"
#include "yatest/trace.hpp"

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdexcept>
#include <sstream>

namespace yatest {

int check(int code)
{
    if (code < 0) throw TcpSocket::Error(strerror(errno));
    return code;
}

TcpSocket::TcpSocket()
    : fd_(check(socket(AF_INET, SOCK_STREAM, 0)))
{
}

TcpSocket::TcpSocket(int fd)
    : fd_(fd)
{
}

TcpSocket::~TcpSocket()
{
    if (fd_) close(fd_);
}

TcpSocket::TcpSocket(TcpSocket&& other)
    : fd_(other.fd_)
{
    other.fd_ = 0;
}

TcpSocket& TcpSocket::operator =(TcpSocket&& other)
{
    std::swap(fd_, other.fd_);
    return *this;
}

void TcpSocket::listenPort(uint16_t port, size_t queue)
{
    YATEST_DEBUG(port << ", " << queue);

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    int optval = 1;
    check(setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)));
    check(bind(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)));
    check(listen(fd_, queue));
}

TcpSocket TcpSocket::acceptClient()
{
    return TcpSocket(check(accept(fd_, 0, 0)));
}

void TcpSocket::terminate()
{
    check(shutdown(fd_, SHUT_RDWR));
}

void TcpSocket::connectTo(const std::string& host, uint16_t port)
{
    YATEST_DEBUG(host << ":" << port);

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) != 1)
    {
        std::ostringstream ss;
        ss << "This is not valid address: " << host;
        throw Error(ss.str());
    }

    check(connect(fd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)));
}

void socketRead(int fd, char* data, int size)
{
    if (recv(fd, data, size, MSG_WAITALL) != size)
       throw TcpSocket::Disconnect("recv has failed");
}

void socketWrite(int fd, const char* data, int size)
{
    if (send(fd, data, size, 0) != size)
       throw TcpSocket::Disconnect("send has failed");
}

std::string TcpSocket::read()
{
    size_t size;
    socketRead(fd_, reinterpret_cast<char*>(&size), sizeof(size_t));

    std::string message(size, 0);
    socketRead(fd_, const_cast<char*>(message.c_str()), message.size());

    YATEST_DEBUG(message);
    return message;
}

void TcpSocket::write(const std::string& message)
{
    YATEST_DEBUG(message);
    size_t size = message.size();

    socketWrite(fd_, reinterpret_cast<char*>(&size), sizeof(size_t));
    socketWrite(fd_, message.c_str(), message.size());
}

TcpSocket::Error::Error(const std::string& message)
    : std::runtime_error(message)
{
}

TcpSocket::Disconnect::Disconnect(const std::string& message)
    : Error(message)
{
}

} // namespace yatest
