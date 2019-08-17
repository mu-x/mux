#include "utils.h"

#include <arpa/inet.h>
#include <stdio.h>

#define thread_local __thread

char* cch_addr_str(const struct sockaddr_in* addr)
{
    char addr_buf[INET_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET, &addr->sin_addr, addr_buf, INET_ADDRSTRLEN);

    static __thread char full_addr_buf[INET_ADDRSTRLEN * 2] = {0};
    sprintf(full_addr_buf, "%s:%d", addr_buf, ntohs(addr->sin_port));
    return full_addr_buf;
}

int cch_log_enabled = 0;
