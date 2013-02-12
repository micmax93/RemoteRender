#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED
//#include <boost/thread.hpp>
using namespace std;

class BufferedFileSender
{
    int file;
    int buf_size;
    int total_size;
    vector<void*> file_content;

    void load_file(string fname)
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

    bool send_content(int client)
    {
        write(client,&total_size,sizeof(total_size));
        write(client,&buf_size,sizeof(buf_size));
        int chksum;
        read(client,&chksum,sizeof(chksum));
        if(chksum!=(int)file_content.size())
        {
            return false;
        }

        for(unsigned int i=0; i<file_content.size(); i++)
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

public:
    BufferedFileSender(string fname)
    {
        buf_size=512;
        load_file(fname);
    }

    ~BufferedFileSender()
    {
        for(unsigned int i=0; i<file_content.size(); i++)
        {
            free(file_content[i]);
        }
        file_content.clear();
    }

    bool sendTo(int client)
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
};


#endif // CLIENT_HPP_INCLUDED
