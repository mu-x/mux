#include "utils.hpp"

int main(int argc, char **argv)
{
    int port = (argc > 1) ? std::stoi(argv[1]) : 6666;

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    Fd server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &ON, sizeof ON);

    if (bind(server, (struct sockaddr*)&servAddr, sizeof servAddr) < 0)
        throw exceptionErrno("bind server");

    if (listen(server, 10) < 0)
        throw exceptionErrno("listen server");

    std::cout << "Listening on: " << servAddr << std::endl;
    for (;;)
    {
        struct sockaddr_in peerAddr;
        socklen_t len = sizeof peerAddr;
        Fd peer = accept(server, (struct sockaddr *)&peerAddr, &len);
        std::cout << "Got peer from: " << peerAddr << std::endl;

        Fd client = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(client, (struct sockaddr*)&peerAddr, sizeof peerAddr) < 0) {
            std::cerr << "Error connect: " << strerror(errno) << std::endl;
            continue;
        }

        std::vector<char> buffer(1024);
        int size = read(client, buffer.data(), buffer.size() - 1);
        if (size <= 0) {
            std::cerr << "Error read:" << strerror(errno) << std::endl;
            continue;
        }

        buffer[size] = 0;
        std::cout << "Connect & read: " << buffer.data() << std::endl;
    }

}
