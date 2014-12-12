TARGET = aladdin_test

TEMPLATE = app
CONFIG += qt

PRECOMPILED_HEADER =        \
    main.h                  \

SOURCES =                   \
    main.cpp                \
    request.cpp             \
    request_queue.cpp       \
    request_reciever.cpp    \
    request_worker.cpp      \

HEADERS +=                  \
    main.h                  \
    request.h               \
    request_queue.h         \
    request_reciever.h      \
    request_worker.h        \
