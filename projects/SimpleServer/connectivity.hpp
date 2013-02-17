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

    void assignPointers();

public:

    struct sockaddr_in *sockaddr_in_ptr;
    struct sockaddr *sockaddr_ptr;
    struct in_addr *in_addr_ptr;
    in_addr_t *s_addr_ptr;
    socklen_t *addrlen_ptr;

    Addr();
    Addr(string name,int port);
    Addr(int port);
    Addr(const Addr &copy);
    Addr& operator=(Addr &copy);

    bool initByName(string name,int port);
    bool initByIP(string ip,int port);
    bool initHost(int port);

    int getPort();
    string getIP();
};

class Connection
{
    protected:
    int my_socket;
    Addr addr;
    bool active;

    virtual bool init();

public:

    Connection();
    operator int();

    void disconnect();

    bool initByAddr(Addr addr);
    void initByCopy(int existingSocket,Addr addr);

    int getSocket();
    int getPort();
    string getIP();
    bool isActive();
};

class Host: public Connection
{
    protected:
    virtual bool init();

    public:
    Connection waitForClient();
};


int writeNetInt(int client,int *msg);
int readNetInt(int client,int *msg);

void writeInt(int fd, int value);
void writeChar(int fd, char value);
int readInt(int fd, int def = -1);
int readChar(int fd, char def = ' ');

#endif // KLASY_HPP_INCLUDED
