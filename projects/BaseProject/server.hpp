#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED
#include <signal.h>

namespace server
{
    Host host;
    bool active=false;
    std::vector<int> children;

    void signalHandler(int sig)
    {
        active=false;
        write(host,"q",1);
    }

    void initConection(int port)
    {
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
        signal(SIGTERM,signalHandler);
        printf("Server initialized on port %i using pid=%i.\n",port,getpid());
        active=true;
    }

    void mainLoop(void (*client_handler)(Connection))
    {
        while(active and host.isActive())
        {
            Connection newClient=host.waitForClient();
            int pid=fork();
            if(pid==0)
            {
                host.disconnect();
                client_handler(newClient);
                exit(0);
            }
            else
            {
                newClient.disconnect();
                children.push_back(pid);
            }
        }
    }
}

#endif // SERVER_HPP_INCLUDED
