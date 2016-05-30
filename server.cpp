#include "server.h"

Server::Server(int port):
    server_socket_(port),
    field_(),
    player_type_(WHITE),
    opponents_type_(BLACK)
{
    server_socket_.Bind();
}

void Server::ListenToConnections()
{
    server_socket_.Listen();
    server_socket_.Accept();
    strcpy(buffer_, "Connected");
    server_socket_.SendData(buffer_);
    printf("Client connected\n");
    field_.Draw(player_type_);

}

void Server::SendData()
{
    strcpy(buffer_, server_socket_.RecieveData());
    int* data = new int[2];
    SplitBuffer(buffer_, data);
    int row = data[0];
    int col = data[1];
    field_.Move(row, col, opponents_type_);
    field_.Draw(player_type_);
    printf("To skip turn press 0\nInput row:");
    scanf("%d", &row);
    if(row != 0)
    {
        printf("Input col:");
        scanf("%d", &col);
    }
    else
    {
        col = 0;
    }
    while(!field_.Move(row, col, player_type_))
    {
        field_.Draw(player_type_);
        printf("Wrong Turn\nTo skip turn press 0\nInput row:");
        scanf("%d", &row);
        if(row != 0)
        {
            printf("Input col:");
            scanf("%d", &col);
        }
        else
        {
            col = 0;
        }
    }
    field_.Draw(player_type_);
    CreateBuffer(row, col, buffer_);
    server_socket_.SendData(buffer_);

    SendData();
}
