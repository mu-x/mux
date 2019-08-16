#ifndef CCH_SERVER_H
#define CCH_SERVER_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define CCH_MAX_CLIENTS 100
#define CCH_BUFFER_SIZE 1024

#define thread_local __thread
#define CCH_FREE_P(STRUCT, FUNC) void FUNC ## p (struct STRUCT** p) { if (*p) FUNC(*p); *p = NULL; }

const char* addr_str(const struct sockaddr_in* addr);

struct cch_server {
    int fd;
    struct sockaddr_in addr;

    pthread_mutex_t mutex;
    struct cch_server_connection* connections[CCH_MAX_CLIENTS];
};

struct cch_server* cch_server_init(in_port_t port);
void cch_server_serve(struct cch_server* server);
void cch_server_free(struct cch_server* server);
CCH_FREE_P(cch_server, cch_server_free);

struct cch_server_connection {
    struct cch_server* server;
    int fd;
    struct sockaddr_in addr;
    pthread_t thread;
};

struct cch_server_connection* cch_server_connection_init(int fd, struct cch_server* s);
void cch_server_connection_serve(struct cch_server_connection* c);
void cch_server_connection_free(struct cch_server_connection* c);
CCH_FREE_P(cch_server_connection, cch_server_connection_free);

#endif // CCH_SERVER_H
