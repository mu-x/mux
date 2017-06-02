#include <cstring>
#include <cstdlib>

#include <fstream>
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
    #include <boost/thread.hpp>
    #include <boost/optional.hpp>
#endif // defined(BOOST)

#if defined(QT)
    #include <QtCore/QMutex>
#endif // defined(QT)

#define PRINT(out) std::cout << out << std::endl

template<typename Value>
void print(const Value& value) {
    std::cout << value << std::endl;
}

template<typename Value, typename ... Values>
void print(const Value& value, const Values& ... values) {
    std::cout << value << " ";
    print(values ...);
}
