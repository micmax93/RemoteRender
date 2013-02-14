#include <iostream>
#include <vector>
#include <stdio.h>
#include <fcntl.h>
#include "protocol.hpp"
#include "connectivity.hpp"
#include "utilities.hpp"
#include "server.hpp"
#include "client.hpp"
using namespace std;

void new_client(Connection klient)
{
    char msg;
    read(klient,&msg,sizeof(msg));
    if(msg==protocol::GET_HOST_PID)
    {
        int pid=getppid();
        write(klient,&pid,sizeof(pid));
    }
    else if(msg==protocol::NEW_CLIENT_REQ)
    {
        BufferedFileSender bf("foto.jpg");
        bf.sendTo(klient);
    }
    klient.disconnect();
}

int main(int argc, char **argv)
{
    if(argc<3)
    {
        printf("Invalid initialization, use: '%s start port' or %s stop pid'\n",argv[0],argv[0]);
        exit(0);
    }

    string cmd(argv[1]);
    int port=atoi(argv[2]);

    if(cmd=="start")
    {
        if(!fork())
        {
            server::initConection(port);
            server::mainLoop(new_client);
        }
    }
    else if(cmd=="stop")
    {
        Connection conn;
        conn.initByAddr(Addr("localhost",port));

        char msg=protocol::GET_HOST_PID;
        write(conn,&msg,sizeof(msg));

        int pid;
        read(conn,&pid,sizeof(pid));
        kill(pid,SIGTERM);
    }
    else
    {
        printf("Invalid initialization, use: '%s start port' or %s stop'\n",argv[0],argv[0]);
        exit(0);
    }

    return 0;
}
