#ifndef SOCKET_H
#define SOCKET_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#ifndef WIN32
#define WIN32
#endif
#pragma comment(lib,"Ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#define MAKEWORD_LOW_ORDER_BYTE 2
#define MAKEWORD_HIGH_ORDER_BYTE 2
typedef int in_addr_t;
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
typedef int SOCKET;
#endif

void Error(const char *msg);

class Socket
{
protected:
    SOCKET sockfd_;
    struct sockaddr_in addr_;
public:
    Socket(int port);
    virtual ~Socket();
};

#endif // SOCKET_H
