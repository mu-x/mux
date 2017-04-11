#include "utils.hpp"


int main(int argc, char **argv)
{
    std::string host((argc > 1) ? argv[1] : "localhost");
    int publicPort = (argc > 2) ? std::stoi(argv[2]) : 6666;
    int servPort = (argc > 2) ? std::stoi(argv[2]) : 7777;

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(servPort);

    Fd server = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &ON, sizeof ON);

    if (bind(server, (struct sockaddr*)&servAddr, sizeof servAddr) < 0)
        throw exceptionErrno("bind server");

    Fd client = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(client, SOL_SOCKET, SO_REUSEADDR, &ON, sizeof ON);

    if (bind(client, (struct sockaddr*)&servAddr, sizeof servAddr) < 0)
        throw exceptionErrno("bind client");

    std::cout << "listen on: " << servAddr << std::endl;
    if (listen(server, 10) < 0)
        throw exceptionErrno("listen server");

    struct sockaddr_in publicAddr;
    publicAddr.sin_family = AF_INET;
    inet_pton(AF_INET, host.c_str(), &publicAddr.sin_addr);
    publicAddr.sin_port = htons(publicPort);

    std::cout << "connect to: " << publicAddr << std::endl;
    if (connect(client, (struct sockaddr*)&publicAddr, sizeof publicAddr) < 0)
        throw exceptionErrno("connect");

    Fd incoming = accept(server, 0, 0);

    std::string message = "hello";
    if (write(incoming, message.c_str(), message.size()) <= 0)
        throw exceptionErrno("write");
}

