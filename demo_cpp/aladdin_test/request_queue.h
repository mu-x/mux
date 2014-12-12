#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include "main.h"
#include "request.h"

namespace aladdin_test {


/** The Request safe Pointer */
typedef QSharedPointer<Request> RequestPtr;

/**
 * The Request Queue.
 * Provides interface of threadsafe queue for request.
 */
class RequestQueue {
    RequestQueue()  {}  /**< Inits emty queue (hidden for singletone) */
    ~RequestQueue() {}  /**< Delete queue */

public:
    RequestPtr dequeue();               /**< Dequeues request */
    void enqueue(RequestPtr request);   /**< Enqueues request */

    /**< Resurns singletone instance */
    static RequestQueue& instance();

private:
    QMutex              mutex;
    QQueue<Request*>    queue;
};


} // namespace aladdin_test

#endif // REQUEST_QUEUE_H
