#include "server.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_connection.h"

struct cch_server* cch_server_init(in_port_t port) {
    struct cch_server* server = (struct cch_server*) malloc(sizeof(struct cch_server));
    if (!server)  return NULL;
    memset(server, 0, sizeof(struct cch_server));

    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!server->fd || pthread_mutex_init(&server->mutex, NULL)) {
        cch_server_free(server);
        return NULL;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    socklen_t addr_size = sizeof(server->addr);
    if (setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) ||
        bind(server->fd, (struct sockaddr*) &addr, sizeof(addr)) ||
        listen(server->fd, CCH_MAX_CLIENTS) ||
        getsockname(server->fd, (struct sockaddr*) &server->addr, &addr_size)
    ) {
        cch_server_free(server);
        return NULL;
    }

    return server;
}

void cch_server_serve(struct cch_server* server) {
    CCH_LOG(server->addr, "Server started, fd: %d", server->fd);
    while (1) {
        int fd = accept(server->fd, (struct sockaddr*) NULL, 0);
        if (!fd) {
            break;
        }

        pthread_mutex_lock(&server->mutex);
        int connectionId;
        for (connectionId = 0; server->connections[connectionId]; ++connectionId) {
            if (connectionId == CCH_MAX_CLIENTS) {
                errno = EAGAIN;
                CCH_LOG(server->addr, "Out of memory for new clients, limit: %d", CCH_MAX_CLIENTS);
                pthread_mutex_unlock(&server->mutex);
                break;
            }
        }

        server->connections[connectionId] = _cch_sconn_init(fd, server);
        if (!server->connections[connectionId]) {
            pthread_mutex_unlock(&server->mutex);
            break;
        }

        pthread_mutex_unlock(&server->mutex);
    }
}

void cch_server_free(struct cch_server* server) {
    if (server->fd) {
        close(server->fd);
        server->fd = 0;
    }

    pthread_mutex_lock(&server->mutex);
    struct _cch_sconn** c;
    for (c = server->connections; c != server->connections + CCH_MAX_CLIENTS; ++c) {
        pthread_mutex_unlock(&server->mutex);
        _cch_sconn_freep(c);
        pthread_mutex_lock(&server->mutex);
    }

    pthread_mutex_unlock(&server->mutex);
    free(server);
}


