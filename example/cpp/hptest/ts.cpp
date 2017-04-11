#include "utils.hpp"

int main(int argc, char** argv)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(12345);

    std::cout << "bind" << std::endl;
    if (bind(s, (struct sockaddr *) &servAddr, sizeof servAddr) < 0)
        throw exceptionErrno("bind");

    std::cout << "listen 3" << std::endl;
    if (listen(s, 3) < 0)
        throw exceptionErrno("listen");

    std::string a;
    std::cin >> a;
}
