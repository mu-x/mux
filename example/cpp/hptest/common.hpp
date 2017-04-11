#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <thread>
#include <chrono>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

template <typename ostream>
ostream& operator<<(ostream& os, const struct sockaddr_in& addr)
{
    char host[1024];
    inet_ntop(AF_INET, &addr.sin_addr, host, sizeof host);
    return os << host << ":" << ntohs(addr.sin_port);
}

inline
struct sockaddr_in sockAddrIn(int port, const std::string& host = std::string())
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;

    if (host.empty()) {
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        int ret = inet_pton(AF_INET, host.c_str(), &addr.sin_addr);
        if (ret < 0)
            throw std::domain_error("inet_pton(" + host +
                                             "): " + std::to_string(ret));
    }

    addr.sin_port = htons(port);
    return addr;
}

class TcpSocket
{
    int _sock;

public:
    explicit
    TcpSocket(const struct sockaddr_in* addr = nullptr, bool reuseAddr = false)
    {
        _sock = ::socket(AF_INET, SOCK_STREAM, 0);
        if (_sock == 0)
           throw std::domain_error("socket(AF_INET, SOCK_STREAM, 0)");

        if (reuseAddr) {
            int value = 1;
            int r1 = ::setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR,
                                  &value, sizeof value);
            if (r1 < 0)
                throw std::domain_error("setsockopt(SO_REUSEADDR): " +
                                        std::to_string(r1));

            int r2 = ::setsockopt(_sock, SOL_SOCKET, SO_REUSEPORT,
                                  &value, sizeof value);
            if (r1 < 0)
                throw std::domain_error("setsockopt(SO_REUSEPORT): " +
                                        std::to_string(r2));
        }

        if (addr) {
            int ret = ::bind(_sock, (struct sockaddr*)addr, sizeof *addr);
            if (ret < 0) {
                std::ostringstream ss;
                ss << "bind(" << *addr << "): " << strerror(errno)
                   << " (reuseAddr=" << reuseAddr << ")";
                throw std::domain_error(ss.str());
            }
        }
    }

    explicit
    TcpSocket(TcpSocket& server, struct sockaddr_in* addr = nullptr)
    {
        socklen_t len = addr ? (sizeof *addr) : 0;
        _sock = ::accept(server._sock, (struct sockaddr*)addr, &len);
        if (_sock == 0)
            throw std::domain_error("accept()");
    }

    ~TcpSocket()
    {
        close();
    }

    void close()
    {
        if (_sock) {
            ::close(_sock);
            _sock = 0;
        }
    }

    void listen(int backlog = 10)
    {
        int ret = ::listen(_sock, backlog);
        if (ret < 0)
            throw std::domain_error("listen: " + std::to_string(ret));
    }

    void connect(const struct sockaddr_in& addr)
    {
        int ret = ::connect(_sock, (struct sockaddr*)&addr, sizeof addr);
        if (ret < 0) {
            std::ostringstream ss;
            ss << "connect(" << addr << "): " << strerror(errno);
            throw std::domain_error(ss.str());
        }
    }

    void address(struct sockaddr_in* addr)
    {
        socklen_t len = addr ? (sizeof *addr) : 0;
        int ret = ::getsockname(_sock, (struct sockaddr*)addr, &len);
        if (ret < 0)
            throw std::domain_error("getsockname: " + std::to_string(ret));
    }

    template <typename T>
    bool read(T* value)
    {
        return ::read(_sock, value, sizeof *value) == sizeof *value;
    }

    template <typename T>
    bool write(const T& value)
    {
        return ::write(_sock, &value, sizeof value) == sizeof value;
    }
};


