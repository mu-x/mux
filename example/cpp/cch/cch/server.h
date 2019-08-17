#ifndef CCH_SERVER_H
#define CCH_SERVER_H

#include <netinet/in.h>
#include <pthread.h>

#include "utils.h"

// TODO: Allow to configure.
#define CCH_MAX_CLIENTS 1024

/**
 * TCP Chat server for telnet-like clients.
 * Usage: cch_server_serve(cch_server_init(0))
 */
struct cch_server {
    int fd;
    struct sockaddr_in addr;

    pthread_mutex_t mutex;
    struct _cch_sconn* connections[CCH_MAX_CLIENTS];
};

/** Creates a server, bound to port. */
struct cch_server* cch_server_init(in_port_t port);

/** Servers client connections untill interrupt. */
void cch_server_serve(struct cch_server* server);

/** Close connections, free resoutrces. */
void cch_server_free(struct cch_server* server);
#define cch_server_freep(p) CCH_FREEP(cch_server, p)

#endif // CCH_SERVER_H
