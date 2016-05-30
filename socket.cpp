#include "socket.h"

void Error(const char *msg)
{
    perror(msg);
    exit(1);
}

Socket::Socket(int port)
{
#ifdef WIN32

    WSADATA wsa_data;
    sockfd_ = INVALID_SOCKET;

    int result;
    result = WSAStartup(MAKEWORD(MAKEWORD_LOW_ORDER_BYTE , MAKEWORD_HIGH_ORDER_BYTE), &wsa_data);
    if (result != 0)
    {
        Error("WSAStartup ERROR");
    }

    ZeroMemory(&addr_, sizeof(&addr_));

#endif
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd_ < 0)
    {
        Error("Failed to create socket");
    }
}

Socket::~Socket()
{
#ifdef WIN32
    closesocket(sockfd_);
    WSACleanup();
#else
    close(sockfd_);
#endif
}
