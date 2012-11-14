#include <iostream>
#include <vector>
#include <queue>
#include <boost/thread.hpp>
#include "utilities.hpp"
#include "connectivity.hpp"
#include "server.hpp"
using namespace std;
using namespace boost;

void new_client(Connection klient)
{
	string msg="Idziemy na piwo?\n";
    write(klient,msg.c_str(),msg.size());
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
