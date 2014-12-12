#ifndef REQUEST_WORKER_H
#define REQUEST_WORKER_H

#include "main.h"
#include "request_queue.h"

namespace aladdin_test {


class RequestWorker : public QThread
{
    Q_OBJECT
public:
    explicit RequestWorker(QObject *parent = 0);
};


} // namespace aladdin_test

#endif // REQUEST_WORKER_H
