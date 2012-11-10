#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include "klasy.hpp"
using namespace std;
using namespace boost;

void new_client(int socket, string addr)
{
    cout << socket << " " << addr << endl;
}

void funkcja(Addr adr)
{
    cout << adr.getIP() << " : " << adr.getPort() << endl;
}

int main()
{
    thread t1(new_client,10,"net.com");
    cout << "Hello world!" << endl;
    t1.join();
    return 0;
}
