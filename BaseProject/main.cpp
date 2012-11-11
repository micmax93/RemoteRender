#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include "klasy.hpp"
using namespace std;
using namespace boost;

void new_client(Connection klient)
{
    char buf[51];
    buf[50]=0;
    while(read(klient,buf,50))
    {
        printf("%i: %s",(int)klient,buf);
        for(int i=0;i<50;i++)
        {
            buf[i]=0;
        }
    }
    klient.disconnect();
}

int main()
{


    Host host;
    if(!host.initByAddr(Addr(6668)))
    {
        printf("Could not inialize host connection.\n");
        exit(0);
    }

    Server reader(host,new_client);
    reader.start();

    host.disconnect();
    return 0;
}
