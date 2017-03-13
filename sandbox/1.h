#include <cstring>
#include <cstdlib>

#include <future>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <type_traits>
#include <vector>

#if defined(BOOST)
    #include <boost/thread.h>
#endif // defined(BOOST)

#if defined(QT)
    #include <QtCore/QMutex>
#endif // defined(QT)

#define PRINT(out) std::cout << out << std::endl

