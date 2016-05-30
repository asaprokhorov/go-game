#include "client.h"
#include "server.h"
#include "gamefield.h"
#include <stdlib.h>
#include <iostream>
#define PORT 5522
#define IP "127.0.0.1"
int main()
{
    char type;
    std::cout << "Choose type: Server(s) or Client(c)\n";
    std::cin >> type;
    if(type == 's')
    {
        Server s(PORT);
        s.ListenToConnections();
        s.SendData();
    }
    else if(type == 'c')
    {
        Client c;
        c.ConnectTo(IP, PORT);
        c.SendData();
    }
    else
    {
        printf("Try again\n");
        return 0;
    }
}
