#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

namespace server
{
    Host host;
    bool active=false;
    boost::thread_group threads;

    void initConection(int argc, char **argv)
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

    void mainLoop(void (*client_handler)(Connection))
    {
        while(active and host.isActive())
        {
            Connection newClient=host.waitForClient();
            threads.add_thread(new boost::thread(client_handler,newClient));
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
}

#endif // SERVER_HPP_INCLUDED
