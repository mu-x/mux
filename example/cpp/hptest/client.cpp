#include "common.hpp"

enum class Mode {
    NONE,
    REUSE_ADDR,  // reuse address after connectiong to 3rd party
    SIM_OPEN,    // simultaneous open on next port
    BOTH,        // REUSE_ADDR + SIM_OPEN
};

Mode parseMode(const std::string& str)
{
    if (str == "r") return Mode::REUSE_ADDR;
    if (str == "s") return Mode::SIM_OPEN;
    if (str == "b") return Mode::BOTH;
    throw std::domain_error("Unknown mode: " + str);
}

int main(int argc, char **argv)
{
    std::string host((argc > 1) ? argv[1] : "localhost");
    int port = (argc > 2) ? std::stoi(argv[2]) : 6666;
    Mode mode = parseMode((argc > 3) ? argv[3] : "r");

    struct sockaddr_in selfAddr, peerAddr;
    {
        TcpSocket medSock(nullptr, true);
        auto medAddr = sockAddrIn(port, host);
        medSock.connect(medAddr);

        medSock.address(&selfAddr);
        if (!medSock.read(&peerAddr))
            throw std::domain_error("could not read peer address");

        std::cout << "Self address: " << selfAddr << std::endl;
        std::cout << "Peer address: " << peerAddr << std::endl;
    }

    if (mode != Mode::REUSE_ADDR) {
        selfAddr.sin_port = htons(ntohs(selfAddr.sin_port) + 1);
        peerAddr.sin_port = htons(ntohs(peerAddr.sin_port) + 1);
    }

    bool connected = false;
    int data;
    TcpSocket outSock(&selfAddr, true);
    while (!connected) {
        try {
            outSock.connect(peerAddr);
            std::cout << "Connected to: " << peerAddr << std::endl;
            connected = true;
        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    if (outSock.read(&data))
        std::cout << "Read: " << data << std::endl;
    else
        std::cerr << "Reading failure" << std::endl;
}
