#include "clientsocket.h"

ClientSocket::ClientSocket(in_addr_t ip, int port) : Socket(port)
{
    addr_.sin_addr.s_addr = ip;
}

void ClientSocket::Connect()
{
    if(connect(sockfd_, (struct sockaddr*)&addr_, sizeof(addr_)) < 0) {
        Error("Failed to connect");
    }
    printf("Connecting to server...");
    if (recv(sockfd_, buffer_, SIZE_OF_BUFFER, 0) <= 0) {
        Error("Failed to connect");
    }
    printf("%s\n", buffer_);
}

void ClientSocket::SendData(char* msg)
{
    strcpy(buffer_, msg);
    send(sockfd_, buffer_, strlen(buffer_) + 1, 0);
}

char* ClientSocket::RecieveData()
{
    recv(sockfd_, buffer_, strlen(buffer_) + 1, 0);
    return buffer_;
}

ClientSocket::~ClientSocket()
{

}

