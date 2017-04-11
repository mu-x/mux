#include "utils.hpp"

#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
    if (argc == 1)
        return 0;

    std::cout << argv[1] << std::endl;

    int s = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << fcntl(s, F_GETFD) << " ? " << FD_CLOEXEC << std::endl;

    if (argc > 2)
    {
        struct sockaddr_in servAddr;
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(7777);
        if (bind(s, (struct sockaddr *) &servAddr, sizeof servAddr) < 0)
            throw exceptionErrno("bind");

        if (listen(s, 10) < 0)
            throw exceptionErrno("listen");
    }

    pid_t p = fork();
    if (p == 0) {
        execve("a.out", argv + 2, 0);
        ::exit(-1);
    }

    if (argc > 2) close(s);
    std::cout << "Forked & closed " << p << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(std::stoi(argv[1])));
}
