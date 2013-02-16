#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED
#include <cv.h>
#include <highgui.h>
#include "Shader.h"
#include "Scene.h"
using namespace std;
using namespace cv;

namespace client
{
    uchar *test_jpg(int *file_size)
    {
        vector<int> params;// (aparams, aparams + sizeof(aparams) / sizeof(int) );
        params.push_back(CV_IMWRITE_JPEG_QUALITY);
        params.push_back(100);

        Mat img=imread("foto.jpg");
        vector<uchar> vbuf;
        bool status;
        status=imencode(".jpg",img,vbuf,params);
        if(!status)
        {
            printf("File encoding error.\n");
            exit(0);
        }
        *file_size=vbuf.size();
        uchar *buf=vbuf.data();
        return buf;
    }

    bool new_client(Connection klient)
    {
        printf("recieved connection %s \n",klient.getIP().c_str());

        int buf_size=protocol::BUF_SIZE;
        writeNetInt(klient,&buf_size);
        printf("buf_size= %i \n",buf_size);

        int xml_size;
        readNetInt(klient,&xml_size);
        printf("xml size= %i \n",xml_size);

        int xml_buf_count=ceil((float)xml_size/(float)buf_size);
        writeNetInt(klient,&xml_buf_count);
        printf("xml_buf_count= %i \n",xml_buf_count);

        BufferedFileReciever xml_data(xml_size,buf_size);
        xml_data.initDownload(klient);
        printf("xml downloaded\n");

        FILE *xml_file=xml_data;

//
//        renderer::initRenderer();
//        renderer::loadScene(xml_file);
//        Image img=renderer::renderImage();
//        renderer::cleanRenderer();
        Shader *shader = initRenderer();
        Scene *scene = loadScene(xml_file, shader);
        Image img=renderImage(shader, scene);


        int jpg_size=img.size();
        uchar *jpg_data=img.getDataPtr();
        writeNetInt(klient,&jpg_size);
        printf("jpg, size= %i\n",jpg_size);

        int chksum=0;
        readNetInt(klient,&chksum);
        printf("checksum= %i\n",chksum);

        int jpg_buf_count=ceil((float)jpg_size/(float)buf_size);
        if(chksum!=jpg_buf_count)
        {
            printf("checksum FAIL, expected= %i\n",jpg_buf_count);
            return false;
        }

        BufferedFileSender bf(jpg_data,jpg_size,buf_size);
        bf.sendTo(klient);
        printf("FILE SEND\n");

        return true;
    }

    void new_connection(Connection klient)
    {
        printf("New connection!!! \n");
        char msg;
        read(klient,&msg,sizeof(msg));
        printf("Recieved mark: %c\n",msg);
        if(msg==protocol::GET_HOST_PID)
        {
            int pid=getppid();
            write(klient,&pid,sizeof(pid));
        }
        else if(msg==protocol::NEW_CLIENT_REQ)
        {
            printf("New client!!! \n");
            new_client(klient);
        }
        klient.disconnect();
    }
}
#endif // CLIENT_HPP_INCLUDED
