#include "utils.hpp"

int main(int argc, char** argv)
{
    for (int n = 1; n < 999; n++)
    {
        int c = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in servAddr;
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);
        servAddr.sin_port = htons(12345);

        std::cout << "connect " << n << std::endl;
        if (connect(c, (struct sockaddr *) &servAddr, sizeof servAddr) < 0)
            throw exceptionErrno("connect");

        std::cout << "connected" << n << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::minutes(5));
}
