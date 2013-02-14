#include <stdio.h>
#include <fcntl.h>
#include <vector>
#include <cv.h>
#include <highgui.h>
using namespace std;
using namespace cv;

int main(int argc,char **argv)
{
    if(argc<3)
    {
        printf("Invalid use: %s infile outfile\n",argv[0]);
        exit(0);
    }
    //int aparams[] = {CV_IMWRITE_JPEG_QUALITY, 100};
    vector<int> params;// (aparams, aparams + sizeof(aparams) / sizeof(int) );
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(100);

    Mat img=imread(argv[1]);
    vector<uchar> vbuf;
    bool status;
    status=imencode(".jpg",img,vbuf,params);
    if(!status)
    {
        printf("File encoding error.\n");
        exit(0);
    }


    int file=open(argv[2],O_CREAT | O_TRUNC | O_RDWR,0666);
    if(file<0)
    {
        printf("File open error.\n");
        exit(0);
    }

    int file_size=vbuf.size();
    uchar *buf=vbuf.data();
    write(file,buf,file_size);
    close(file);
    return 0;
}
