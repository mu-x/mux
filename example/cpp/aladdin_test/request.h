#ifndef REQUEST_H
#define REQUEST_H

#include "main.h"

namespace aladdin_test {


/** The Request. Presentates request for workers. */
class Request {
    // Is empty yet
};

/** The Stopper. Presenates stop signal of nucessury. */
enum Stopper {
    NON_STOP,   /**< Need no stop   */
    NEED_STOP   /**< Stop is needed */
};

/**
 * Returns request or NULL if there're no requests.
 * Allocates memory for request, do nothing if stopSignal=NEED_STOP.
 */
Request* GetRequest(Stopper stopSignal = NON_STOP) throw();

/**
 * Processes request without realocation
 * Do nothing if stopSignal=NEED_STOP
 */
void ProcessRequest(Request* request, Stopper stopSignal = NON_STOP) throw();

// Options:
const int HAS_REQUEST_VERA = 50;    /**< % of return Request() */

const int PRECESS_MIN_TIME = 100;   /**< Minimal time for process request */
const int PRECESS_MAX_TIME = 1000;  /**< Maximal time for process request */


} // namespace aladdin_test

#endif // REQUEST_H
