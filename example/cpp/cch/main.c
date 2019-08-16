#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cch/server.h"

int main(int argc, char** argv) {
    struct cch_server server = {0};
    server.addr.sin_family = AF_INET;
    server.addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server.addr.sin_port = htons(0);

    if (argv[1]) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printf("Usage: %s [port]\n", argv[0]);
            return 0;
        }

        server.addr.sin_port = htons(atoi(argv[1]));
        if (server.addr.sin_port == 0) {
            printf("Wrong port number '%s', see -h\n", argv[1]);
            return 1;
        }
    }

    printf("Starting server on 0.0.0.0:%d...\n", ntohs(server.addr.sin_port));
    if (cch_server_init(&server) != 0) {
        printf("Unale to start server: %s\n", strerror(errno));
        return 2;
    }

    char addrBuf[INET_ADDRSTRLEN] = {0};
    printf("Server is started on %s:%d\n",
        inet_ntop(AF_INET, &server.addr.sin_addr, addrBuf, INET_ADDRSTRLEN),
        ntohs(server.addr.sin_port));

    if (cch_server_serve(&server) != 0) {
        printf("Unale to server clients: %s\n", strerror(errno));
    } else {
        printf("Server has stopped\n");
    }

    cch_server_free(&server);
    return 0;
}
