#include "server_connection.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include "server.h"

// TODO: Allow to configure.
#define CCH_BUFFER_SIZE 1024
#define CCH_ENDL '\n'
#define CCH_SEND_TIMEOUT_S 1
#define CCH_RECV_TIMEOUT_S 60

static void send_message_from(struct _cch_sconn* sender, const char* buffer, int size) {
    // TODO: Remove mutex usage, just delay connection removal.
    pthread_mutex_lock(&sender->server->mutex);
    struct _cch_sconn** conns = sender->server->connections;
    for (struct _cch_sconn** conn = conns; conn != conns + CCH_MAX_CLIENTS; ++conn) {
        if (*conn && *conn != sender) {
            char* addr = cch_addr_str(&(*conn)->addr);
            int addr_len = strlen(addr);
            addr[addr_len] = ' ';
            send((*conn)->fd, addr, addr_len + 1, /*flags*/ 0);

            // TODO: Handle the result somehow. We do not do anything, because
            // connection's thread is likelly sill uses it.
            send((*conn)->fd, buffer, size, /*flags*/ 0);
        }
    }
    pthread_mutex_unlock(&sender->server->mutex);
}

static void process_connection(struct _cch_sconn* conn) {
    char buffer[CCH_BUFFER_SIZE];
    int size = 0;
    while (1) {
        if (size == CCH_BUFFER_SIZE) {
            CCH_LOG(conn->addr, "Buffer of size %d is full", CCH_BUFFER_SIZE);
        }

        int read = recv(conn->fd, &buffer + size, CCH_BUFFER_SIZE - size, /*flags*/ 0);
        if (read <= 0)
            return;

        size += read;
        char* begin = buffer;
        char* end = begin;
        for (; end < buffer + size; ++end) {
            if (*end == '\n') {
                send_message_from(conn, begin, end - begin + 1);
                begin = end + 1;
            }
        }

        int used = begin - buffer;
        if (used) {
            int left = size - used;
            if (left) memcpy(buffer, begin, left);
            size -= used;
        }
    }
}

static void remove_connection(struct _cch_sconn* conn) {
    pthread_mutex_lock(&conn->server->mutex);
    struct _cch_sconn** conns = conn->server->connections;
    for (struct _cch_sconn** c = conns; c != conns + CCH_MAX_CLIENTS; ++c) {
        if (*c == conn) {
            c = NULL;
            break;
        }
    }
    pthread_mutex_unlock(&conn->server->mutex);
}

static void* run_thread(void* c) {
    struct _cch_sconn* conn = (struct _cch_sconn*) c;
    CCH_LOG(conn->addr, "Client is connected, fd: %d", conn->fd);
    process_connection(conn);

    CCH_LOG(conn->addr, "Client is disconnected, fd: %d", conn->fd);
    remove_connection(conn);

    _cch_sconn_freep(&conn);
    return NULL;
}

struct _cch_sconn* _cch_sconn_init(int fd, struct cch_server* server) {
    struct _cch_sconn* conn
        = (struct _cch_sconn*) malloc(sizeof(struct _cch_sconn));
    if (!conn) return NULL;
    memset(conn, 0, sizeof(struct _cch_sconn));

    conn->server = server;
    conn->fd = fd;

    socklen_t addr_size = sizeof(conn->addr);
    struct timeval send_timeout = { CCH_SEND_TIMEOUT_S, 0 };
    struct timeval recv_timeout = { CCH_RECV_TIMEOUT_S, 0 };
    if (getpeername(fd, (struct sockaddr*) &conn->addr, &addr_size) ||
        setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &send_timeout, sizeof(send_timeout)) == -1 ||
        setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout)) == -1 ||
        pthread_create(&conn->thread, /*attrs*/ NULL, &run_thread, conn)
    ) {
        CCH_LOG(conn->addr, "Unabe to setup socket: %s", strerror(errno));
        _cch_sconn_freep(&conn);
        return NULL;
    }

    return conn;
}

void _cch_sconn_free(struct _cch_sconn* conn) {
    if (conn->thread) {
        pthread_join(conn->thread, NULL);
        conn->thread = 0;
    }

    close(conn->fd);
    free(conn);
}
