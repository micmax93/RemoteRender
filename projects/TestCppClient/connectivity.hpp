#ifndef CONNECTIVITY_HPP_INCLUDED
#define CONNECTIVITY_HPP_INCLUDED
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <ctype.h>
#include <string>
using namespace std;

class Addr
{
    struct sockaddr_in addr;
    socklen_t addrlen;

    void assignPointers()
    {
        sockaddr_in_ptr=(&addr);
        sockaddr_ptr=(struct sockaddr*)(&addr);
        in_addr_ptr=(&addr.sin_addr);
        s_addr_ptr=(&addr.sin_addr.s_addr);
        addrlen_ptr=(&addrlen);
    }

public:

    struct sockaddr_in *sockaddr_in_ptr;
    struct sockaddr *sockaddr_ptr;
    struct in_addr *in_addr_ptr;
    in_addr_t *s_addr_ptr;
    socklen_t *addrlen_ptr;

    Addr()
    {
        addr.sin_family=AF_INET;
        addrlen=sizeof(addr);
        assignPointers();
    }

    Addr(string name,int port)
    {
        addr.sin_family=AF_INET;
        addrlen=sizeof(addr);
        assignPointers();
        initByName(name,port);
    }

    Addr(int port)
    {
        addr.sin_family=AF_INET;
        addrlen=sizeof(addr);
        assignPointers();
        initHost(port);
    }

    Addr(const Addr &copy)
    {
        addr=*copy.sockaddr_in_ptr;
        addrlen=*copy.addrlen_ptr;
        assignPointers();
    }

    Addr& operator=(Addr &copy)
    {
        addr=*copy.sockaddr_in_ptr;
        addrlen=*copy.addrlen_ptr;
        return *this;
    }

    bool initByName(string name,int port)
    {
        struct hostent *host;
        host=gethostbyname(name.c_str());
        if(host==NULL)
        {
            return false;
        }
        addr.sin_addr=*((struct in_addr*)(host->h_addr));
        addr.sin_port=htons(port);
        return true;
    }

    bool initByIP(string ip,int port)
    {
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
        addr.sin_port=htons(port);
        return true;
    }

    bool initHost(int port)
    {
        addr.sin_addr.s_addr=INADDR_ANY;
        addr.sin_port=htons(port);
        return true;
    }

    int getPort()
    {
        return (int)(ntohs(addr.sin_port));
    }

    string getIP()
    {
        char buf[20];
        string ip;
        inet_ntop(AF_INET, &addr.sin_addr, buf, addrlen);
        ip=buf;
        return ip;
    }

};

struct transmition_info
{
    int code;   ///kod weryfikacyjny

    unsigned int comand;    ///komenda (rodzaj transmisji)
    unsigned long long buf_size;  ///rozmiar bufora
    unsigned long long data_size; ///rozmiar danych
};

class Connection
{
    protected:
    int my_socket;
    Addr addr;
    bool active;

    virtual bool init()
    {
        disconnect();
        my_socket=socket(AF_INET,SOCK_STREAM,0);
        if(my_socket<0)
        {
            return false;
        }

        int status;
        status=connect(my_socket,addr.sockaddr_ptr,*addr.addrlen_ptr);
        if(status<0)
        {
            close(my_socket);
            return false;
        }
        active=true;
        return true;
    }

public:

    Connection()
    {
        active=false;
    }

    operator int()
    {
        return my_socket;
    }

    void disconnect()
    {
        if(active)
        {
            close(my_socket);
            active=false;
        }
    }

    bool initByAddr(Addr addr)
    {
        this->addr=addr;
        return init();
    }

    void initByCopy(int existingSocket,Addr addr)
    {
        this->addr=addr;
        my_socket=existingSocket;
        active=true;
    }

    int getSocket()
    {
        return my_socket;
    }

    int getPort()
    {
        return addr.getPort();
    }

    string getIP()
    {
        return addr.getIP();
    }

    bool isActive()
    {
        return active;
    }
};

class Host: public Connection
{
    protected:
    virtual bool init()
    {
        disconnect();
        my_socket=socket(AF_INET,SOCK_STREAM,0);
        if(my_socket<0)
        {
            return false;
        }

        int optval=1;
        setsockopt(my_socket,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));

        int status;
        status=bind(my_socket,addr.sockaddr_ptr,*addr.addrlen_ptr);
        if(status<0)
        {
            close(my_socket);
            return false;
        }

        status=listen(my_socket,5);
        if(status<0)
        {
            close(my_socket);
            return false;
        }

        active=true;
        return true;
    }

    public:
    Connection waitForClient()
    {
        Addr new_addr;
        Connection client;
        int new_sock;
        new_sock=accept(my_socket, new_addr.sockaddr_ptr, new_addr.addrlen_ptr);
        if(new_sock>0)
        {
            client.initByCopy(new_sock,new_addr);
        }
        return client;
    }
};


int writeNetInt(int client,int *msg)
{
    int nmsg=0;
    nmsg=htonl(*msg);
    return write(client,&nmsg,sizeof(int));
}

int readNetInt(int client,int *msg)
{
    int nmsg=0,status=0;
    status=read(client,&nmsg,sizeof(int));
    *msg=ntohl(nmsg);
    return status;
}

#endif // KLASY_HPP_INCLUDED
