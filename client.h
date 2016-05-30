#ifndef CLIENT_H
#define CLIENT_H
#include "socket.h"
#include "clientsocket.h"
#include "gamefield.h"

#define SIZE_OF_BUFFER 2048

class Client
{
    char buffer_[SIZE_OF_BUFFER];
    ClientSocket* client_socket_;
    GameField field_;
    int player_type_;
    int opponents_type_;
public:
    Client();
    void ConnectTo(char* address, int port);
    void SendData();
    ~Client();
};

#endif // CLIENT_H
