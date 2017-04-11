#include "utils.hpp"

int main(int argc, char **argv)
{
    std::string host((argc > 1) ? argv[1] : "localhost");
    int port = (argc > 2) ? std::stoi(argv[2]) : 6666;

    std::string msg = "hello";
    struct sockaddr_in peerAddr;
    Fd client = socket(AF_INET, SOCK_DGRAM, 0);
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        inet_pton(AF_INET, host.c_str(), &addr.sin_addr);
        addr.sin_port = htons(port);

        if (sendto(client, msg.data(), msg.size(), 0,
                   (struct sockaddr *)&addr, sizeof addr) <= 0)
            throw exceptionErrno("sendto mediator");

        socklen_t len = sizeof addr;
        if (recvfrom(client, &peerAddr, sizeof peerAddr, 0,
                     (struct sockaddr *)&addr, &len) <= 0)
            throw exceptionErrno("recvfrom mediator");

        std::cout << "Peer address: " << peerAddr << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (sendto(client, msg.data(), msg.size(), 0,
               (struct sockaddr *)&peerAddr, sizeof peerAddr) <= 0)
        throw exceptionErrno("sendto peer");

    socklen_t len = sizeof peerAddr;
    std::vector<char> buffer(1024);
    int size = recvfrom(client, buffer.data(), buffer.size(), 0,
                        (struct sockaddr *)&peerAddr, &len);
    if (size <= 0)
        throw exceptionErrno("recvfrom peer");

    buffer[size] = 0;
    std::cout << "From " << peerAddr << " got: " << buffer.data() << std::endl;
}
