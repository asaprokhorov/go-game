#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include "socket.h"

#define SIZE_OF_BUFFER 2048
#define NUMBER_OF_LISTENERS 2

class ServerSocket : public Socket
{
    SOCKET client_fd_;
    char buffer_[SIZE_OF_BUFFER];
public:
    ServerSocket(int port);
    void Bind();
    void Accept();
    void Listen();
    void SendData(char* msg);
    char* RecieveData();
    ~ServerSocket();
};

#endif // SERVERSOCKET_H
