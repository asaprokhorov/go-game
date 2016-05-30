#ifndef SERVER_H
#define SERVER_H
#include "serversocket.h"
#include "clientsocket.h"
#include "gamefield.h"

#define SIZE_OF_BUFFER 2048

class Server
{
    ServerSocket server_socket_;
    //ClientSocket client_socket_;
    char buffer_[SIZE_OF_BUFFER];
    GameField field_;
    int player_type_;
    int opponents_type_;
public:
    Server(int port);
    void ListenToConnections();
    void SendData();
};

#endif // SERVER_H
