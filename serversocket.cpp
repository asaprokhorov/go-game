#include "serversocket.h"

ServerSocket::ServerSocket(int port) : Socket(port)
{
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);
}

void ServerSocket::Bind()
{
    if(bind(sockfd_, (struct sockaddr*)&addr_, sizeof(addr_)) != 0)
    {
        Error("Failed to bind socket");
    }
}

void ServerSocket::Accept()
{
    socklen_t addrlen = sizeof(addr_);
    client_fd_ = accept(sockfd_, (struct sockaddr*)&addr_, &addrlen);
    if(client_fd_ < 0)
    {
        Error("Failed to connect");
    }
}

void ServerSocket::Listen()
{
    if(listen(sockfd_, NUMBER_OF_LISTENERS) != 0)
    {
        Error("Failed to listen");
    }
}

void ServerSocket::SendData(char* msg)
{
    strcpy(buffer_, msg);
    send(client_fd_, buffer_, strlen(buffer_) + 1, 0);
}

char* ServerSocket::RecieveData()
{
    recv(client_fd_, buffer_, strlen(buffer_) + 1, 0);
    return buffer_;
}

ServerSocket::~ServerSocket()
{
#ifdef WIN32
    closesocket(sockfd_);
    WSACleanup();
#else
    close(sockfd_);
#endif
}
