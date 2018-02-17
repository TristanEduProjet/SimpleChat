#ifndef NETWORK_HPP_INCLUDED
#define NETWORK_HPP_INCLUDED

#include <cstdint>
#include <unistd.h>

//#define WIN32
#if defined(WIN32) || defined(_WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>
#ifdef _MSC_VER
#pragma comment(lib, "ws2_32.lib") // Need to link with Ws2_32.lib
//#pragma comment (lib, "Mswsock.lib")
#endif // _MSC_VER

#define SHUT_RD SD_RECEIVE
#define SHUT_WR SD_SEND
#define SHUT_RDWR SD_BOTH
#define inet_ntop InetNtop

//#elif defined (linux) || defined (_POSIX_VERSION) || defined (_POSIX2_C_VERSION) || defined (_XOPEN_VERSION)
#else

//#include <sys/types.h>
//#include <arpa/inet.h>
//#else
//#error not defined for this platform

//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> //IPPROTO_IP IPPROTO_TCP
#include <netdb.h>
#include <sys/time.h>

/* for matching Microsoft's typedef */
#define closesocket(s) close(s)
typedef struct sockaddr_in SOCKADDR_IN, *PSOCKADDR_IN, *LPSOCKADDR_IN;
typedef struct sockaddr SOCKADDR, *PSOCKADDR, *LPSOCKADDR;
typedef struct sockaddr_storage SOCKADDR_STORAGE, *PSOCKADDR_STORAGE;
typedef struct timeval TIMEVAL, *PTIMEVAL, *LPTIMEVAL;
typedef int SOCKET;
#define INVALID_SOCKET -1 //(SOCKET)(~0)
#define SOCKET_ERROR -1

#endif // WIN32

typedef union SockAddress {
    SOCKADDR addr;
    SOCKADDR_IN addr_in;
    SOCKADDR_STORAGE addr_storage;
} SockAddress;

SockAddress new_socket_address(const std::uint16_t port);
SOCKET new_socket_tcp();
SOCKET new_socket_udp();

#define PORT 5669

#endif // NETWORK_HPP_INCLUDED
