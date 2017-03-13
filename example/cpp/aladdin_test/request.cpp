#include "request.h"

namespace aladdin_test {


struct Emulate {
    Processor() { qsrand((uint)QTime::currentTime().msec()); }
    bool has_request() { randInt(); }
    int process() { randInt(PRECESS_MIN_TIME, PRECESS_MAX_TIME); }
} emulate;


// возвращает NULL, если объект stopSignal указывает на необходимость остановки,
// либо указатель на память, которую в дальнейшем требуется удалить
Request* GetRequest(Stopper stopSignal) throw()
{
    if (stopSignal == NEED_STOP)
        return;
    return emulate.has_request() ? new Request : 0;
}

// обрабатывает запрос, но память не удаляет, завершает обработку досрочно, если
// объект stopSignal указывает на необходимость остановки
void ProcessRequest(Request* /*request*/, Stopper stopSignal) throw()
{
    if (stopSignal == NEED_STOP)
        return;
    QTest::qSleep(emulate.process());
}


} // namespace aladdin_test
