#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cv.h>
#include <highgui.h>
#define TIXML_USE_STL
#include "xml/tinyxml.h"
#include "Shader.h"
#include "Object.h"
#include "Cube.h"
#include "Sphere.h"
#include "Reader.h"

glm::mat4 matP; //rzutowania
glm::mat4 matV; //widoku

using namespace std;
using namespace cv;

//Ustawienia okna i rzutowania
int windowPositionX = 100;
int windowPositionY = 100;
int windowWidth = 400;
int windowHeight = 400;
float cameraAngle = 45.0f;

Shader *shader;

GLuint vao;
GLuint bufVertices;
GLuint bufColors;
GLuint bufNormals;

Scene *scene;

void onIdle() {
}

void displayFrame() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    matP = glm::perspective(cameraAngle, (float) windowWidth / (float) windowHeight, 1.0f, 100.0f);
    matV = glm::lookAt(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    shader->bind();
    glUniformMatrix4fv(shader->getProjectionMatrixUniform(), 1, false, glm::value_ptr(matP));
    glUniformMatrix4fv(shader->getViewMatrixUniform(), 1, false, glm::value_ptr(matV));

    printf("DRAW!\n");
    // TODO draw

    shader->bind();

    if (scene != NULL) {
        std::vector<Object*> *objects = scene->getObjects();
        printf("Drawing %d objects.\n", objects->size());
        for (int i = 0; i < objects->size(); i++) {
            std::cout << "Draw object!" << std::endl;
            Object *o = (*objects)[i];
            o->draw(shader);
        }
    }
    printf("Scene drawn.\n");
    //    glutSwapBuffers();
}

void onChangeSize(int w, int h) {
    glViewport(0, 0, w, h);
    windowWidth = w;
    windowHeight = h;
}

void initGLUT(int *argc, char** argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowPosition(windowPositionX, windowPositionY);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("RemoteRenderer");
    glutHideWindow();

    glutReshapeFunc(onChangeSize);
    glutDisplayFunc(displayFrame);
    glutIdleFunc(onIdle);
}

void initGLEW() {
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "%s\n", glewGetErrorString(err));
        exit(1);
    }
}

void setupShaders() {
    std::string v = "vertex.txt";
    std::string f = "fragment.txt";
    shader = new Shader(v, "", f);
}

void initOpenGL() {
    setupShaders();
    glEnable(GL_DEPTH_TEST);
}

void cleanShaders() {
    delete shader;
}

void freeVBO() {
    glDeleteBuffers(1, &bufVertices);
    glDeleteBuffers(1, &bufColors);
    glDeleteBuffers(1, &bufNormals);
}

void freeVAO() {
    glDeleteVertexArrays(1, &vao);
}

void getViewportSize(int *width, int *height) {
    GLint tmp[4];
    glGetIntegerv(GL_VIEWPORT, tmp);
    *width = tmp[2];
    *height = tmp[3];
}

void readPixels(float* pixels, int &w, int &h) {
    glReadPixels(0, 0, w, h, GL_RGB, GL_FLOAT, pixels);
}

void saveImage(float* pixels, int width, int height) {
    Mat image(width, height, CV_32FC3);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            image.at<Vec3f > (width - x - 1, y)[0] = 255 * pixels[3 * (x * height + y) + 0];
            image.at<Vec3f > (width - x - 1, y)[1] = 255 * pixels[3 * (x * height + y) + 1];
            image.at<Vec3f > (width - x - 1, y)[2] = 255 * pixels[3 * (x * height + y) + 2];
        }
    }
    imwrite("tmp.jpg", image);
}

Mat getImage(float* pixels, int width, int height) {
    Mat image(width, height, CV_32FC3);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            image.at<Vec3f > (width - x - 1, y)[0] = 255 * pixels[3 * (x * height + y) + 0];
            image.at<Vec3f > (width - x - 1, y)[1] = 255 * pixels[3 * (x * height + y) + 1];
            image.at<Vec3f > (width - x - 1, y)[2] = 255 * pixels[3 * (x * height + y) + 2];
        }
    }
    return image;
}

void testXml() {
    TiXmlDocument doc("scene.xml");
    if (doc.LoadFile()) {

        TiXmlElement *root = doc.FirstChildElement("scene");
        if (root) {
            TiXmlElement *objects = root->FirstChildElement("objects");
            TiXmlElement *camera = root->FirstChildElement("camera");
            //
            TiXmlElement *tmp;


            float x, y, z;

            tmp = camera->FirstChildElement("eye")->FirstChildElement("x");
            if (tmp) {
                x = atof(tmp->FirstChild()->Value());
                printf("x=%f\n", x);
            }

            tmp = camera->FirstChildElement("eye")->FirstChildElement("y");
            if (tmp) {
                y = atof(tmp->FirstChild()->Value());
                printf("y=%f\n", y);
            }

            tmp = camera->FirstChildElement("eye")->FirstChildElement("z");
            if (tmp) {
                z = atof(tmp->FirstChild()->Value());
                printf("z=%f\n", z);
            }
        }
    }
}



class Image
{
    bool valid;
    vector<uchar> vbuf;
    int file_size;
    uchar *data;

    public:
    Image(Mat img,int quality=95)
    {
        vector<int> params;
        params.push_back(CV_IMWRITE_JPEG_QUALITY);
        params.push_back(quality);

        valid=imencode(".jpg",img,vbuf,params);

        file_size=vbuf.size();
        data=vbuf.data();
    }
    ~Image()
    {
        vbuf.clear();
    }

    bool isValid()
    {
        return valid;
    }

    uchar *getDataPtr()
    {
        if(valid)
        {
            return data;
        }
        else
        {
            return NULL;
        }
    }

    int size()
    {
        return file_size;
    }
};

namespace renderer
{
    void initRenderer()
    {
        char *argv[]={"Renderer"};
        int argc=1;
        initGLUT(&argc, argv);
        initGLEW();
        initOpenGL();
        glViewport(0, 0, windowWidth, windowHeight);
    }

    void loadScene(FILE *xml)
    {
        Reader reader(shader);
        reader.loadFile(xml);
        if (reader.isValid()) {
            scene = reader.getScene();
        }
    }

    Image renderImage()
    {
        displayFrame();

        int w, h;
        getViewportSize(&w, &h);
        float *pixels = new float[w * h * 3];
        readPixels(pixels, w, h);
        int quality=95;
        Mat img=getImage(pixels, w, h);
        return Image(img,quality);
    }

    void cleanRenderer()
    {
        freeVAO();
        freeVBO();
        cleanShaders();
    }
}
