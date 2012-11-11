#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include "klasy.hpp"
using namespace std;
using namespace boost;

void new_client()
{
    Connection klient;
    klient.initByAddr(Addr("localhost",6668));
    write(klient,"qweocdkb",8);
    klient.disconnect();
}

int main()
{


    Host serwer;
    if(!serwer.initByAddr(Addr(6668)))
        {exit(0);}

    thread t1(new_client);

    Connection nowy=serwer.waitForClient();

    if(!nowy.isActive())
        {exit(0);}

    t1.join();

    char buf[6];
    buf[5]=0;

    cout << read(nowy,buf,5) << ": " << buf << endl;
    cout << read(nowy,buf,5) << ": " << buf << endl;

    nowy.disconnect();
    serwer.disconnect();
    return 0;
}
