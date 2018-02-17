#if defined(WIN32) || defined(_WIN32)
#undef UNICODE
  #ifndef _MSC_VER
  #define _WIN32_WINNT  0x501 //manual hack mingw
  #endif // _MSC_VER
#include <w32api.h>
#include <ws2tcpip.h>
#endif // WIN32

#include "network.hpp"
#include "utils.hpp"
#include <cstring> //memset
#include <stdexcept>

SockAddress new_raw_address() {
    SockAddress address /*= { 0 }*/;
    memset(&address, 0x0, sizeof(address));
    //ZeroMemory(&address, sizeof(address));
    return address;
}

SockAddress new_socket_address(const std::uint16_t port) {
    SockAddress address = new_raw_address();
    address.addr_in.sin_family = AF_INET; //IP protocol familly
    address.addr_in.sin_port = htons(port); //listening port
    address.addr_in.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr( real_ip().c_str() ); //IP address auto/all
    return address;
}

SOCKET new_socket_tcp() {
    return socket(AF_INET, SOCK_STREAM, /*IPPROTO_IP*/IPPROTO_TCP);
}

SOCKET new_socket_udp() {
    return socket(AF_INET, SOCK_DGRAM, /*IPPROTO_IP*/IPPROTO_UDP);
}

//extern int getaddrinfo (const char*,const char*,const struct addrinfo*, struct addrinfo**); //manual hack

struct addrinfo* get_host_info(const char default_port[]) {
    struct addrinfo *result = NULL;
    struct addrinfo hints /*= {0}*/;
    #if defined(WIN32) || defined(_WIN32)
    ZeroMemory(&hints, sizeof(hints));
    #else
    memset(&hints, 0x0, sizeof(hints));
    #endif
    hints.ai_family = AF_INET; //AF_UNSPEC //IPv4 & IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE; //wildcard IP
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    const int ret = getaddrinfo(NULL, default_port, &hints, &result);
    if(ret != 0)
        throw std::logic_error(gai_strerror(ret));
    //else {
        return result;
    //}
    ///socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    /**
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        int sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; // Success
        close(sfd);
    }

    if (rp == NULL) { //No address succeeded
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);
    */
}
