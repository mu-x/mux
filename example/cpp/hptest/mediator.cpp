#include "common.hpp"

int main(int argc, char **argv)
{
    int port = (argc > 1) ? std::stoi(argv[1]) : 6666;
    auto servAddr = sockAddrIn(port);

    TcpSocket server(&servAddr, true);
    server.listen();
    std::cout << "Listening on: " << port << " ..." << std::endl;
    while (1)
    {
        struct sockaddr_in addr1, addr2;
        socklen_t len1 = sizeof addr1, len2 = sizeof addr2;

        TcpSocket client1(server, &addr1);
        std::cout << "Client 1: " << addr1 << std::endl;

        TcpSocket client2(server, &addr2);
        std::cout << "Client 2: " << addr2 << std::endl;

        if (client1.write(addr2) && client2.write(addr1))
            std::cout << "Exchanged" << std::endl;
        else
            std::cout << "Failed" << std::endl;
    }
}
