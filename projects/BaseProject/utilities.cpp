#include "utilities.hpp"
using namespace std;

    void BufferedFileSender::load_file(string fname)
    {
        file=open(fname.c_str(),O_RDONLY);
        if(file<0)
        {
            printf("Error: no file to send!\n");
            exit(0);
        }

        total_size=0;
        void *buf;
        int curr_size;

        do
        {
            buf=malloc(buf_size);
            curr_size=read(file,buf,buf_size);
            total_size+=curr_size;
            file_content.push_back(buf);
        }
        while(curr_size==buf_size);

        close(file);
    }

    void BufferedFileSender::link_buffer(uchar *buf,int size)
    {
        total_size=size;
        int curr=0;

        while(curr<total_size)
        {
            file_content.push_back(buf+curr);
            curr+=buf_size;
        }
    }

    bool BufferedFileSender::send_content(int client)
    {
        for(uint i=0; i<file_content.size(); i++)
        {
            if(total_size>buf_size)
            {
                write(client,file_content[i],buf_size);
                total_size-=buf_size;
            }
            else
            {
                write(client,file_content[i],total_size);
                total_size=0;
            }
        }
        return true;
    }

    BufferedFileSender::BufferedFileSender(string fname)
    {
        load_file(fname);
    }

    BufferedFileSender::BufferedFileSender(uchar *buf,int totalSize,int bufSize)
    {
        buf_size=bufSize;
        link_buffer(buf,totalSize);
    }

    BufferedFileSender::~BufferedFileSender()
    {
        for(uint i=0; i<file_content.size(); i++)
        {
            free(file_content[i]);
        }
        file_content.clear();
    }

    bool BufferedFileSender::sendTo(int client)
    {
        if(file_content.empty())
        {
            return false;
        }
        else
        {
            return send_content(client);
        }
    }

    bool BufferedFileReciever::download_content(int client)
    {
        int count=ceil((float)total_size/(float)buf_size);
        void *buf=malloc(buf_size);
        while(count--)
        {
            int n;
            n=read(client,buf,buf_size);
            fwrite(buf,sizeof(char),n,file);
        }
        free(buf);
        fseek(file,0,SEEK_SET);
        return true;
    }

    BufferedFileReciever::BufferedFileReciever()
    {
//        file=tmpfile();
        file=fopen("plik2","w");
        if(file==NULL)
        {
            printf("Temp file error: could not create.\n");
            exit(0);
        }
    }


    BufferedFileReciever::BufferedFileReciever(int totalSize,int bufSize)
    {
        total_size=totalSize;
        buf_size=bufSize;
//        file=tmpfile();
        file=fopen("tmp.xml","w");
        if(file==NULL)
        {
            printf("Temp file error: could not create.\n");
            exit(0);
        }
    }

    void BufferedFileReciever::initDownload(int client)
    {
        download_content(client);
    }

    BufferedFileReciever::~BufferedFileReciever()
    {
        fclose(file);
    }

    FILE* BufferedFileReciever::getFilePtr()
    {
        return file;
    }

    BufferedFileReciever::operator FILE*()
    {
        return file;
    }

