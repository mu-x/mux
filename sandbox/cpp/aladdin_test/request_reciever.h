#ifndef REQUEST_RECIEVER_H
#define REQUEST_RECIEVER_H

#include "main.h"
#include "request_queue.h"

namespace aladdin_test {


class RequestReciever : public QThread
{
    Q_OBJECT
public:
    explicit RequestReciever(QObject *parent = 0);
    
signals:
    
public slots:
    
};


} // namespace aladdin_test

#endif // REQUEST_RECIEVER_H
