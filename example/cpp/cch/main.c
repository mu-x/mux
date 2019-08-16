#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cch/server.h"

int main(int argc, char** argv) {
    in_port_t port = 0;
    if (argv[1]) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printf("Usage: %s [port]\n", argv[0]);
            return 0;
        }

        port = htons(atoi(argv[1]));
        if (port == 0) {
            printf("Wrong port number '%s', see -h\n", argv[1]);
            return 1;
        }
    }

    struct cch_server* server = cch_server_init(htons(port));
    if (!server) {
        printf("Unale to start server on %d: %s\n", port, strerror(errno));
        return 2;
    }

    cch_server_serve(server);
    cch_server_freep(&server);
    return 0;
}
