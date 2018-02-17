#include "utils.hpp"
#include <cstring>
#if !(defined(WIN32) || defined(_WIN32))
#include <arpa/inet.h>
#endif // defined

void print_error(std::string const& message) {
    #ifdef _MSC_VER
        std::cerr << message << ": " << GetLastError() << std::endl; /// << TODO FormatMessage ?
    #else //POSIX (eg. __GNUC__ __MINGW32__ __MINGW64__ __clang__
        perror(message.c_str());
    #endif
}

void print_net_error(std::string const& message) {
    #ifdef _MSC_VER
        std::cerr << message << ": " << WSAGetLastError() << std::endl; /// << TODO FormatMessage ?
    #else //POSIX (eg. __GNUC__ __MINGW32__ __MINGW64__ __clang__
        perror(message.c_str());
    #endif
}

char const* get_ip_str(const PSOCKADDR sa, char *s, size_t maxlen)
{
    #if defined(WIN32) || defined(_WIN32)
    return "<unavailable>"; //InetNTop >= Win08 ...
    #else
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((SOCKADDR_IN*)sa)->sin_addr), s, maxlen);
            break;
        /*case AF_INET6:
            inet_ntop(AF_INET6, &(((SOCKADDR_IN6*)sa)->sin6_addr), s, maxlen);
            break;*/
        default:
            strncpy(s, "Unknown AF", maxlen);
            return NULL;
    }
    return s;
    #endif // WIN32
}


#include <cstdio>
#include <iostream>
//#include "network.hpp"
#if defined(WIN32) || defined(_WIN32)
#include <ws2tcpip.h>
void print_addrinfo(const struct addrinfo *ptr) {
    printf("\tFlags: 0x%x\n", ptr->ai_flags);
    printf("\tFamily: ");
    char ipstringbuffer[46];
    DWORD ipbufferlength = 46;
    switch(ptr->ai_family) {
        case AF_UNSPEC:
            printf("Unspecified\n");
            break;
        case AF_INET:
            printf("AF_INET (IPv4)\n");
            printf("\tIPv4 address %s\n", inet_ntoa(((struct sockaddr_in *) ptr->ai_addr)->sin_addr) );
            break;
        case AF_INET6:
            printf("AF_INET6 (IPv6)\n");
            // the InetNtop function is available on Windows Vista and later
            // sockaddr_ipv6 = (struct sockaddr_in6 *) ptr->ai_addr;
            // printf("\tIPv6 address %s\n", InetNtop(AF_INET6, &sockaddr_ipv6->sin6_addr, ipstringbuffer, 46) );

            // We use WSAAddressToString since it is supported on Windows XP and later
            // The buffer length is changed by each call to WSAAddresstoString
            // So we need to set it for each iteration through the loop for safety
            if(WSAAddressToString((LPSOCKADDR) ptr->ai_addr, (DWORD) ptr->ai_addrlen, NULL, ipstringbuffer, &ipbufferlength))
                printf("WSAAddressToString failed with %u\n", WSAGetLastError() );
            else
                printf("\tIPv6 address %s\n", ipstringbuffer);
            break;
        case AF_NETBIOS:
            printf("AF_NETBIOS (NetBIOS)\n");
            break;
        default:
            std::cout << "Other " << ptr->ai_family << std::endl;
            //break;
    }
    printf("\tSocket type: ");
    switch(ptr->ai_socktype) {
        case 0:
            printf("Unspecified\n");
            break;
        case SOCK_STREAM:
            printf("SOCK_STREAM (stream)\n");
            break;
        case SOCK_DGRAM:
            printf("SOCK_DGRAM (datagram) \n");
            break;
        case SOCK_RAW:
            printf("SOCK_RAW (raw) \n");
            break;
        case SOCK_RDM:
            printf("SOCK_RDM (reliable message datagram)\n");
            break;
        case SOCK_SEQPACKET:
            printf("SOCK_SEQPACKET (pseudo-stream packet)\n");
            break;
        default:
            std::cout << "Other " << ptr->ai_socktype << std::endl;
            break;
    }
    printf("\tProtocol: ");
    switch(ptr->ai_protocol) {
        case 0:
            printf("Unspecified\n");
            break;
        case IPPROTO_TCP:
            printf("IPPROTO_TCP (TCP)\n");
            break;
        case IPPROTO_UDP:
            printf("IPPROTO_UDP (UDP) \n");
            break;
        default:
            std::cout << "Other " << ptr->ai_protocol << std::endl;
            break;
    }
    printf("\tLength of this sockaddr: %zu\n", ptr->ai_addrlen);
    printf("\tCanonical name: %s\n", ptr->ai_canonname);
}
#endif // WIN32
