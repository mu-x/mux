#include "utils.hpp"

int main(int argc, char **argv)
{
    int port = (argc > 1) ? std::stoi(argv[1]) : 6666;

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    Fd server = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &ON , sizeof ON);
    if (bind(server, (struct sockaddr *) &servAddr, sizeof servAddr) < 0)
        throw exceptionErrno("bind");

    struct sockaddr_in addr1, addr2;
    socklen_t len1 = sizeof addr1, len2 = sizeof addr2;
    std::cout << "Bound to: " << servAddr << std::endl;

    std::vector<char> buffer(1024);
    int size;
    for (;;)
    {
        size = recvfrom(server, buffer.data(), buffer.size() - 1, 0,
                        (struct sockaddr *)&addr1, &len1);
        if (size <= 0)
            throw exceptionErrno("recv");

        buffer[size] = 0;
        std::cout << "1st Client " << addr1
                  << " said: " << buffer.data() << std::endl;

        size = recvfrom(server, buffer.data(), buffer.size() - 1, 0,
                        (struct sockaddr *)&addr2, &len2);
        if (size <= 0)
            throw exceptionErrno("recv");

        buffer[size] = 0;
        std::cout << "2st Client " << addr2
                  << " said: " << buffer.data() << std::endl;

        size = sendto(server, &addr2, sizeof addr2, 0,
                   (struct sockaddr *)&addr1, sizeof addr1);
        if  (size != sizeof addr2)
            std::cerr << "Sentto " << addr1 << " error: "
                      << size << " != " << sizeof addr2 << std::endl;

        size = sendto(server, &addr1, sizeof addr1, 0,
                   (struct sockaddr *)&addr2, sizeof addr2);
        if  (size != sizeof addr1)
            std::cerr << "Sentto " << addr2 << " error: "
                      << size << " != " << sizeof addr1 << std::endl;

        std::cout << "Exchanged" << std::endl;
    }
}
