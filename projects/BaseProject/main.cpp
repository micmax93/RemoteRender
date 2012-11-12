#include <iostream>
#include <vector>
#include <boost/thread.hpp>
#include "connectivity.hpp"
#include "server.hpp"
using namespace std;
using namespace boost;

void new_client(Connection klient)
{
    write(klient,"Witam!\n",7);
    klient.disconnect();
}

int main(int argc, char **argv)
{
    server::initConection(argc,argv);

    thread mainThread(server::mainLoop,new_client);

    server::consoleHandler();

    mainThread.join();

    return 0;
}
