#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cch/server.h"

int main(int argc, const char** argv) {
    const char* binary = *argv;
    ++argv;

    in_port_t port = 0;
    for (; *argv; ++argv) {
        if (strcmp(*argv, "-h") == 0 || strcmp(*argv, "--help") == 0) {
            printf("Usage: %s [-v] [port]\n", binary);
            return 0;
        }
        if (strcmp(*argv, "-v") == 0 || strcmp(*argv, "--verbose") == 0) {
            cch_log_enabled = 1;
            continue;
        }

        port = htons(atoi(*argv));
        if (!port) {
            printf("Wrong port number '%s', see -h\n", *argv);
            return 1;
        }
    }

    struct cch_server* server = cch_server_init(htons(port));
    if (!server) {
        printf("Unale to start server on %d: %s\n", port, strerror(errno));
        return 2;
    }

    printf("Start server on %s\n", cch_addr_str(&server->addr));
    cch_server_serve(server);
    cch_server_freep(&server);
    return 0;
}
