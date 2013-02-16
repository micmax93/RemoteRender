#ifndef UTILITIES_HPP_INCLUDED
#define UTILITIES_HPP_INCLUDED
#include <math.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
typedef unsigned char uchar;
using namespace std;

class BufferedFileSender
{
    int file;
    int buf_size;
    int total_size;
    vector<void*> file_content;

    void load_file(string fname);
    void link_buffer(uchar *buf,int size);
    bool send_content(int client);

    BufferedFileSender(string fname);

public:
    BufferedFileSender(uchar *buf,int totalSize,int bufSize);
    ~BufferedFileSender();
    bool sendTo(int client);
};

class BufferedFileReciever
{
    FILE *file;
    int buf_size;
    int total_size;

    bool download_content(int client);
    BufferedFileReciever();

public:

    BufferedFileReciever(int totalSize,int bufSize);
    void initDownload(int client);
    ~BufferedFileReciever();
    FILE *getFilePtr();
    operator FILE*();
};



#endif // UTILITIES_HPP_INCLUDED
