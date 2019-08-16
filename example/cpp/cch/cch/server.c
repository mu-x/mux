#include "server.h"

#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#define LISTEN_LIMIT 100
#define BUFFER_SIZE 1024

static void serve_client(int client) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int read = recv(client, &buffer, BUFFER_SIZE, 0);
        if (read <= 0)
            break;

        int sent = send(client, &buffer, read, 0);
        if (sent <= 0)
            break;
    }
    close(client);
}

int cch_server_init(struct cch_server* server) {
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!server->fd) {
        return 1;
    }

    socklen_t addrSize = sizeof(server->addr);
    if (bind(server->fd, (struct sockaddr*) &server->addr, addrSize) ||
        listen(server->fd, LISTEN_LIMIT) ||
        getsockname(server->fd, (struct sockaddr*) &server->addr, &addrSize)
    ) {
        cch_server_free(server);
        return 2;
    }

    return 0;
}

int cch_server_serve(struct cch_server* server) {
    while (1) {
        int client = accept(server->fd, (struct sockaddr*) NULL, 0);
        if (!client) {
            return 3;
        }

        serve_client(client);
    }
}

void cch_server_free(struct cch_server* server) {
    close(server->fd);
}
