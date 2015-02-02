#ifndef YATEST_TCP_SOCKET_HPP
#define YATEST_TCP_SOCKET_HPP

#include <stdexcept>
#include <string>

namespace yatest {

const size_t DEFAULT_QUEUE = 128;

/** Light weight posix TCP socket wrapper, send/recieve uses discrete protochol
 *  based on message size */
class TcpSocket
{
public:
    /** Creates ready to use TCP socket */
    TcpSocket();
    ~TcpSocket();

    TcpSocket(const TcpSocket&) = delete;
    TcpSocket& operator =(const TcpSocket&) = delete;

    TcpSocket(TcpSocket&& other);
    TcpSocket& operator =(TcpSocket&& other);

    /** Binds and listens on @param port with max @param queue */
    void listenPort(uint16_t port, size_t queue = DEFAULT_QUEUE);
    TcpSocket acceptClient();
    void terminate(); ///< Canceles acceptClient block

    /** Connects to @paran host on @param port */
    void connectTo(const std::string& host, uint16_t port);

    std::string read();
    void write(const std::string& message);

    /** @class TcpSocket related error */
    class Error : public std::runtime_error
    {
    public:
        explicit Error(const std::string& message);
    };

    /** @class TcpSocket disconnection event */
    class Disconnect : public Error
    {
    public:
        explicit Disconnect(const std::string& message);
    };

private:
    TcpSocket(int fd);
    int fd_;
};

} // namespace yatest

#endif // YATEST_TCP_SOCKET_HPP
