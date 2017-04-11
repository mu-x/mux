#include <iostream>
#include <sstream>
#include <functional>
#include <sstream>
#include <string>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <vector>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>
#include <execinfo.h>

static const int ON = 1;

struct Fd
{
    int fd;

    Fd(int _fd) : fd(_fd) {}
    ~Fd() { if(fd) close(); }

    Fd(const Fd&) = delete;
    Fd(Fd&& rhs) : fd(rhs.fd) { rhs.fd = 0; }

    Fd& operator=(const Fd&) = delete;
    Fd& operator=(Fd&& rhs) { std::swap(fd, rhs.fd); }

    operator int() const { return fd; }
    void close() { ::close(fd); fd = 0; }
};

template <typename Exception = std::domain_error>
Exception exception(const std::string& what)
{
    void *buffer[100];
    int n = backtrace(buffer, 100);
    char **strings = backtrace_symbols(buffer, n);

    std::ostringstream ss;
    ss << what << std::endl << std::endl;
    ss << "Backtracke:" << std::endl;
    for (int i = 1; i < n; i++)
        ss << strings[i] << std::endl;

    return Exception(ss.str());
}

template <typename Exception = std::domain_error>
Exception exceptionErrno(const std::string& function)
{
    return exception<Exception>(function + ": " + strerror(errno) +
                                " (" + std::to_string(errno) + ")");
}

template <typename ostream>
ostream& operator<<(ostream& os, const struct sockaddr_in& addr)
{
    char host[1024];
    inet_ntop(AF_INET, &addr.sin_addr, host, sizeof host);
    return os << host << ":" << ntohs(addr.sin_port);
}

Fd boundTcpSocket(const struct sockaddr_in& addr)
{
    Fd sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ON, sizeof ON);
    if (bind(sock, (struct sockaddr*)&addr, sizeof addr) < 0)
        throw exceptionErrno("bind");

    return sock;
}

struct Epoll
{
    Fd fd;

    Epoll() : fd(epoll_create1(0)) {}

    void ctl(uint32_t mode, const Fd& sock, uint32_t events = EPOLLIN) {
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = sock;
        epoll_ctl(fd, mode, sock, &ev);
    }

    std::vector<struct epoll_event> wait() {
        std::vector<struct epoll_event> events(10);
        int n = epoll_wait(fd, events.data(), events.size(), -1);
        if (n == -1)
            throw exceptionErrno("epoll_wait");

        events.resize(n);
        return events;
    }
};


