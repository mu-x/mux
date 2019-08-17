#ifndef CCH_UTILS_H
#define CCH_UTILS_H

#include <netinet/in.h>

/**
 * Formats IP:PORT string, DO NOT FREE IT.
 * TODO: Add support for sockaddr.
 */
char* cch_addr_str(const struct sockaddr_in* addr);

/**
 * Defines inline ffmpeg-like freep which calls free function if pointer is not
 * null and nullifies a pointer.
 */
#define CCH_FREEP(STRUCT, P) do { \
    if (*P) STRUCT##_free(*P); \
    *P = NULL; \
} while(0)

extern int cch_log_enabled;

#define CCH_LOG(ADDR, FORMAT, ...) do { \
    if (cch_log_enabled) \
        fprintf(stderr, "CCH %15s " FORMAT "\n", cch_addr_str(&ADDR), __VA_ARGS__); \
} while(0)

#endif // CCH_UTILS_H
