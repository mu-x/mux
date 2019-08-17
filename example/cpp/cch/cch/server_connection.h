#ifndef CCH_SERVER_CONNECTION_H
#define CCH_SERVER_CONNECTION_H

#include <netinet/in.h>
#include <pthread.h>

#include "utils.h"

struct _cch_sconn {
    struct cch_server* server;
    int fd;
    struct sockaddr_in addr;
    pthread_t thread;
};

/** Creates connection and serves it in a separate thred. */
struct _cch_sconn* _cch_sconn_init(int fd, struct cch_server* s);

/** Closes connection and waits for thread termination. */
void _cch_sconn_free(struct _cch_sconn* c);
#define _cch_sconn_freep(p) CCH_FREEP(_cch_sconn, p)

#endif // CCH_SERVER_CONNECTION_H
