#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "socket.h"

#define SIZE_OF_BUFFER 2048

class ClientSocket : public Socket
{
    char buffer_[SIZE_OF_BUFFER];
public:
    ClientSocket(in_addr_t ip, int port);
    void Connect();
    void SendData(char* msg);
    char* RecieveData();
    ~ClientSocket();
};

#endif // CLIENTSOCKET_H
