#include "request_queue.h"

namespace aladdin_test {


RequestPtr RequestQueue::dequeue()
{
    QMutexLocker lock(mutex);
    return queue.dequeue();
}

void RequestQueue::enqueue(RequestPtr request)
{
    QMutexLocker lock(mutex);
    queue.enqueue(request);
}

static RequestQueue& RequestQueue::instance()
{
    static RequestQueue queue;
    return queue;
}


} // namespace aladdin_test
