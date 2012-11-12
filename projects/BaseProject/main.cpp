#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include "klasy.hpp"
using namespace std;

Host host;
bool active=false;
boost::thread_group clients;

void initServerConection(int argc, char **argv)
{
    if(argc<2)
    {
        printf("Invalid initialization, use: %s port\n",argv[0]);
        exit(0);
    }
    int port=atoi(argv[1]);
    if((port<=1024)||(port>=65535))
    {
        printf("Invalid port number, port should be greater than 1024 and lesser than 65535.\n");
        exit(0);
    }
    if(!host.initByAddr(Addr(port)))
    {
        printf("Could not inialize host connection.\n");
        exit(0);
    }
    active=true;
}

void serverMainLoop(void (*client_handler)(Connection))
{
    while(active and host.isActive())
    {
        Connection newClient=host.waitForClient();
        clients.add_thread(new boost::thread(client_handler,newClient));
    }
}

void consoleHandler()
{
    while(active)
    {
        char c=0;
        scanf("%c",&c);
        if(c=='q')
        {
            active=false;
            write(host,"q",1);
        }
    }
}

void new_client(Connection klient)
{
    write(klient,"Witam!\n",7);
    klient.disconnect();
}

int main(int argc, char **argv)
{
    initServerConection(argc,argv);
    boost::thread serwer(serverMainLoop,new_client);
    consoleHandler();
    serwer.join();
    return 0;
}
