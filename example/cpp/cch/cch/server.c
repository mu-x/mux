#include "server.h"

#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

const char* addr_str(const struct sockaddr_in* addr)
{
    char addr_buf[INET_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET, &addr->sin_addr, addr_buf, INET_ADDRSTRLEN);

    static __thread char full_addr_buf[INET_ADDRSTRLEN * 2] = {0};
    sprintf(full_addr_buf, "%s:%d", addr_buf, ntohs(addr->sin_port));
    return full_addr_buf;
}

struct cch_server* cch_server_init(in_port_t port) {
    struct cch_server* server = (struct cch_server*) malloc(sizeof(struct cch_server));
    if (!server)  return NULL;
    memset(server, 0, sizeof(struct cch_server));

    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!server->fd) {
        cch_server_free(server);
        return NULL;
    }

    if (pthread_mutex_init(&server->mutex, NULL) != 0) {
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
    printf("CCH Server is started on %s\n", addr_str(&server->addr));
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
                pthread_mutex_unlock(&server->mutex);
                break;
            }
        }

        server->connections[connectionId] = cch_server_connection_init(fd, server);
        if (!server->connections[connectionId]) {
            errno = EAGAIN;
            pthread_mutex_unlock(&server->mutex);
            break;
        }

        pthread_mutex_unlock(&server->mutex);
    }
    printf("CCH Server is stopped on %s: %s\n", addr_str(&server->addr), strerror(errno));
}

void cch_server_free(struct cch_server* server) {
    if (server->fd) {
        close(server->fd);
        server->fd = 0;
    }

    pthread_mutex_lock(&server->mutex);
    struct cch_server_connection** c;
    for (c = server->connections; c != server->connections + CCH_MAX_CLIENTS; ++c) {
        pthread_mutex_unlock(&server->mutex);
        cch_server_connection_freep(c);
        pthread_mutex_lock(&server->mutex);
    }

    pthread_mutex_unlock(&server->mutex);
    free(server);
}

static void* run_thread(void* c) {
    struct cch_server_connection* connection = (struct cch_server_connection*) c;
    cch_server_connection_serve(connection);

    pthread_mutex_lock(&connection->server->mutex);
    int i;
    for (i = 0; i < CCH_MAX_CLIENTS; ++i) {
        if (connection->server->connections[i] == connection) {
            connection->server->connections[i] = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&connection->server->mutex);

    cch_server_connection_free(connection);
    return NULL;
}

struct cch_server_connection* cch_server_connection_init(int fd, struct cch_server* server) {
    struct cch_server_connection* connection
        = (struct cch_server_connection*) malloc(sizeof(struct cch_server_connection));
    if (!connection) return NULL;
    memset(connection, 0, sizeof(struct cch_server_connection));

    connection->server = server;
    connection->fd = fd;

    socklen_t addr_size = sizeof(connection->addr);
    if (getsockname(fd, (struct sockaddr*) &connection->addr, &addr_size) != 0) {
        cch_server_connection_freep(&connection);
        return NULL;
    }

    if (pthread_create(&connection->thread, NULL, &run_thread, connection) != 0) {
        cch_server_connection_freep(&connection);
        return NULL;
    }

    return connection;
}

void cch_server_connection_serve(struct cch_server_connection* connection) {
    printf("CCH Client is connected %s\n", addr_str(&connection->addr));
    char buffer[CCH_BUFFER_SIZE];
    while (1) {
        int read = recv(connection->fd, &buffer, CCH_BUFFER_SIZE, 0);
        if (read <= 0)
            break;

        int sent = send(connection->fd, &buffer, read, 0);
        if (sent <= 0)
            break;
    }
    printf("CCH Client is disconnected %s\n", addr_str(&connection->addr));
}

void cch_server_connection_free(struct cch_server_connection* connection) {
    if (connection->thread) {
        pthread_join(connection->thread, NULL);
        connection->thread = 0;
    }

    close(connection->fd);
    free(connection);
}
