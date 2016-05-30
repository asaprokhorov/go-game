#include "client.h"

Client::Client() :
    client_socket_(NULL),
    field_(),
    player_type_(BLACK),
    opponents_type_(WHITE)
{
}

void Client::ConnectTo(char* ip, int port)
{
    client_socket_ = new ClientSocket(inet_addr(ip), port);
    client_socket_->Connect();
    field_.Draw(player_type_);
}

void Client::SendData()
{
    int row;
    int col;
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
    client_socket_->SendData(buffer_);
    strcpy(buffer_, client_socket_->RecieveData());
    int* data = new int[2];
    SplitBuffer(buffer_, data);
    row = data[0];
    col = data[1];
    field_.Move(row, col, opponents_type_);
    field_.Draw(player_type_);
    SendData();
}

Client::~Client()
{
    delete client_socket_;
}
