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
        //write(client,&total_size,sizeof(total_size));
        writeNetInt(client,&total_size);
        printf("Total file size: %i\n",total_size);

        //write(client,&buf_size,sizeof(buf_size));
        writeNetInt(client,&buf_size);
        printf("Buffer size: %i\n",buf_size);

        int chksum=0,n=0;
        //n=read(client,&chksum,sizeof(chksum));
        n=readNetInt(client,&chksum);
        printf("Recieved checksum %i in %i bytes ",chksum,n);
        if(chksum!=(int)file_content.size())
        {
            printf("FAILED\n");
            printf("Expected checksum %i\n",(int)file_content.size());
            return false;
        }
        printf("OK\n");


        printf("Packets send:\n");
        for(unsigned int i=0; i<file_content.size(); i++)
        {
            int c;
            if(total_size>buf_size)
            {
                c=write(client,file_content[i],buf_size);
                total_size-=buf_size;
            }
            else
            {
                c=write(client,file_content[i],total_size);
                total_size=0;
            }
            printf("packet %i : %i bytes\n",i,c);
        }
        printf("FINISHED\n");
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

class XmlElement
{
    vector <string> args_names;
    vector <string> args_values;
    string elements_name;
    protected:
    XmlElement(string name)
    {
        elements_name=name;
    }

    void addArgument(string name,string value)
    {
        args_names.push_back(name);
        args_values.push_back(value);
    }
    void clearArgs()
    {
        args_names.clear();
        args_values.clear();
    }

    void setExistingArgVal(string arg,string value)
    {
        for(uint i=0;i<args_names.size();i++)
        {
            if(args_names[i]==arg)
            {
                args_values[i]=value;
            }
        }
    }

    virtual string getContent();

    public:
    string getXml()
    {
        string xml="";
        xml+="<"+elements_name;
        for(uint i=0;i<args_names.size();i++)
        {
            xml+=" "+args_names[i]+"="+args_values[i];
        }
        xml+=">";
        xml+=getContent();
        xml+="</"+elements_name+">";
        return xml;
    }
};

class XmlGroup: public XmlElement
{
    vector<XmlElement*> children;
    protected:
    XmlGroup(string name): XmlElement(name)
    {
    }

    void addChild(XmlElement *ele)
    {
        children.push_back(ele);
    }
    void clearChildren()
    {
        children.clear();
    }

    virtual string getContent()
    {
        string str="";
        for(uint i=0;i<children.size();i++)
        {
            str+=children[i]->getXml();
        }
        return str;
    }
};


#endif // CLIENT_HPP_INCLUDED
