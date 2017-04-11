#include "utils.hpp"

int main(int argc, char** argv)
{
    std::string host((argc > 1) ? argv[1] : "localhost");
    int port = (argc > 2) ? std::stoi(argv[2]) : 6666;
    int pInc = (argc > 3) ? std::stoi(argv[3]) : 0;

    struct sockaddr_in selfAddr, peerAddr;
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        inet_pton(AF_INET, host.c_str(), &addr.sin_addr);
        addr.sin_port = htons(port);

        Fd sock = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ON, sizeof ON);

        if (connect(sock, (struct sockaddr*)&addr, sizeof addr) < 0)
            throw exception("Connect to mediator failed");

        socklen_t len = sizeof selfAddr;
        getsockname(sock, (struct sockaddr*)&selfAddr, &len);

        if (read(sock, &peerAddr, sizeof peerAddr) != sizeof peerAddr)
            throw exception("Read of peer address failed");

        std::cout << "Self address: " << selfAddr << std::endl;
        std::cout << "Peer address: " << peerAddr << std::endl;
        if (pInc) {
            selfAddr.sin_port = htons(ntohs(selfAddr.sin_port) + 1);
            peerAddr.sin_port = htons(ntohs(peerAddr.sin_port) + 1);
        }
    }

    Fd inSock = boundTcpSocket(selfAddr);
    Fd outSock = boundTcpSocket(selfAddr);

    std::cout << "Listening: " << selfAddr << std::endl;
    if (listen(inSock, 10) < 0)
        throw exceptionErrno("listen");

    std::cout << "Connect to: " << peerAddr << std::endl;
    if (connect(outSock, (struct sockaddr*)&peerAddr, sizeof peerAddr) < 0)
        if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINPROGRESS)
            throw exceptionErrno("connect");

    Epoll epoll;
    epoll.ctl(EPOLL_CTL_ADD, inSock, EPOLLIN);
    epoll.ctl(EPOLL_CTL_ADD, outSock, EPOLLIN | EPOLLOUT);
    while (true)
    for (auto& event : epoll.wait())
    {
        if (event.data.fd == inSock) {
            socklen_t len = sizeof peerAddr;
            Fd peer = accept(inSock, (struct sockaddr *)&peerAddr, &len);
            std::cout << "Incoming connect from: " << peerAddr << std::endl;

            int data = 5;
            int wSize = write(inSock, &data, sizeof data);
            if (wSize == -1 && errno != EAGAIN && errno != EWOULDBLOCK && errno != EINPROGRESS)
                throw exceptionErrno("write");

            std::cout << "Sent: " << data << "(" << wSize << " bytes)" << std::endl;
            return 0;
        }
        else
        if (event.data.fd == outSock) {
            int data;
            int rSize = read(outSock, &data, sizeof data);
            if (rSize <= 0) {
                if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINPROGRESS) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));

                    std::cout << "Reconnect to: " << peerAddr << std::endl;
                    if (connect(outSock, (struct sockaddr*)&peerAddr, sizeof peerAddr) < 0)
                        if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINPROGRESS)
                            throw exceptionErrno("connect");
                }
                continue;
            }

            std::cout << "Outgoind connect recv: " << rSize << " bytes" << std::endl;
            std::cout << "Read: " << data << std::endl;
            return 0;
        }
    }
}
