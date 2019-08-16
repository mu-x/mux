#include <netinet/in.h>
#include <arpa/inet.h>

struct cch_server {
    int fd;
    struct sockaddr_in addr;
};

int cch_server_init(struct cch_server* server);
int cch_server_serve(struct cch_server* server);
void cch_server_free(struct cch_server* server);
