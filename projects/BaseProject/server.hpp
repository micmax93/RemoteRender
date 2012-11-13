#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

class Semaphore
{
    int count;
    boost::mutex outer_mx;
    boost::mutex  inner_mx;

    public:

    Semaphore()
    {
        count=0;
        inner_mx.lock();
    }

    void get()
    {
        outer_mx.lock();
        if(count>0)
        {
            count--;

            if(count>0)
                {inner_mx.unlock();}

            outer_mx.unlock();
        }
        else
        {
            outer_mx.unlock();
            inner_mx.lock();
            get();
        }
    }

    void add(int n=1)
    {
        outer_mx.lock();
        count+=n;
        inner_mx.unlock();
        outer_mx.unlock();
    }
};

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
