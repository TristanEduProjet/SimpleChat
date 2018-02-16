#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <string>
#include "network.hpp"

/*#if defined(__MINGW32__) || defined (__MINGW64__)
    #define std_thread  mingw_stdthread::thread
#else
    #define std_thread std::thread
#endif // defined mingw*/

/*#if defined(WIN32) || defined(_WIN32)
    #define memzero(var) ZeroMemory(&(var), sizeof(var))
#else
    #define memzero(var) memset(&(var), 0x0, sizeof(var))
#endif*/

#ifdef _MSC_VER
    //TODO WinBase.h
    /*#ifndef UNICODE
    #define UNICODE
    #endif*/
#else
    #include <cerrno>
#endif

void print_error(std::string const& message);
void print_net_error(std::string const& message);
#define print_wsa_error print_net_error

char const* get_ip_str(const PSOCKADDR sa, char *s, size_t maxlen);

#endif // UTILS_HPP_INCLUDED
