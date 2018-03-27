#include "h.hpp"

#define MUX_DECLARE_HANDLE_BEGIN(CLASS, HANDLE, DEFAULT, DELETE) \
    class CLASS \
    { \
        HANDLE m_handle; \
        \
    public: \
        using Handle = HANDLE; \
        using Class = CLASS; \
        operator Handle() { return m_handle; } \
        \
        Class(Handle handle = DEFAULT): m_handle(handle) {} \
        ~Class() { if (m_handle != DEFAULT) DELETE(m_handle); } \
        \
        Class(Class&) = delete; \
        Class& operator=(Class&) = delete; \
        Class(Class&& other): m_handle(other.m_handle) { other.m_handle = DEFAULT; } \
        Class& operator=(Class&& other) { std::swap(m_handle, other.m_handle); return *this; } \

#define MUX_DECLARE_HANDLE_CONSTRUCTOR(CREATE) \
        template<typename ... Args> \
        Class(Args ... args): m_handle(CREATE(args ...)) {}

#define MUX_DECLARE_HANDLE_FUNCTION(CALL, FUNCTION) \
        template<typename ... Args> \
        auto FUNCTION(Args ... args) -> decltype(CALL(m_handle, args ...)) \
        { return CALL(m_handle, args ...); }

#define MUX_DECLARE_HANDLE_END \
    };

MUX_DECLARE_HANDLE_BEGIN(File, FILE*, nullptr, fclose)
    MUX_DECLARE_HANDLE_CONSTRUCTOR(fopen)
    MUX_DECLARE_HANDLE_FUNCTION(fprintf, print)
MUX_DECLARE_HANDLE_END

int main(int, const char** /*argv*/)
{
    File f("/tmp/f.txt", "w");
    f.print("hello world");
}

