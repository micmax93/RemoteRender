#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "connectivity.hpp"

int main(int argc,char **argv)
{
    if(argc<4)
    {
        printf("Invalid use: %s addr port filename\n",argv[0]);
        exit(0);
    }
    int port=atoi(argv[2]);
    Addr addr(string(argv[1]),port);

    int file=open(argv[3],O_CREAT | O_TRUNC | O_RDWR,0666);
    if(file<0)
    {
        printf("File open error.\n");
        exit(0);
    }

    Connection serwer;
    serwer.initByAddr(addr);
    if(!serwer.isActive())
    {
        printf("Connection error.\n");
        exit(0);
    }


    // "przywitanie się" z serwerem
    char ping='#';
    write(serwer,&ping,sizeof(ping));

    int total_size,buf_size,count;
    // odbiera rozmiar całego pliku
    read(serwer,&total_size,sizeof(total_size));
    // odbiera rozmiar bufora
    read(serwer,&buf_size,sizeof(buf_size));
    // wylicza ilość buforów do odebrania
    count=ceil((float)total_size/(float)buf_size);
    // wysyła tą ilość (taki jakby checksum)
    write(serwer,&count,sizeof(count));

    //odebranie i zapis bufforów
    void *buf=malloc(buf_size);
    while(count--)
    {
        int n;
        n=read(serwer,buf,buf_size);
        write(file,buf,n);
    }
    close(file);

    serwer.disconnect();
    return 0;
}
