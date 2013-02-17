#ifndef RENDERER_H
#define	RENDERER_H

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
#include <tinyxml.h>
#include "Shader.h"
#include "Object.h"
#include "Cube.h"
#include "Sphere.h"
#include "Reader.h"

using namespace std;
using namespace cv;

class Image
{
    bool valid;
    vector<uchar> vbuf;
    int file_size;
    uchar *data;

    public:
    Image()
    {
        valid=false;
    }
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


void displayFrame(Shader *shader, Scene *scene, int windowWidth, int windowHeight) {
    float cameraAngle = 45.0f;

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 matP = glm::perspective(cameraAngle, (float) windowWidth / (float) windowHeight, 1.0f, 100.0f);
    glm::mat4 matV = glm::lookAt(
            glm::vec3(scene->getEyeX(), scene->getEyeY(), scene->getEyeZ()),
            glm::vec3(scene->getLookAtX(), scene->getLookAtY(), scene->getLookAtZ()),
            //            glm::vec3(-10, -10, -10),
            //            glm::vec3(0, 0, 0),
            glm::vec3(0.0f, 1.0f, 0.0f));

    shader->bind();
    glUniformMatrix4fv(shader->getProjectionMatrixUniform(), 1, false, glm::value_ptr(matP));
    glUniformMatrix4fv(shader->getViewMatrixUniform(), 1, false, glm::value_ptr(matV));

    printf("Draw scene!");
    shader->bind();

    if (scene != NULL) {
        std::vector<Object*> *objects = scene->getObjects();
        for (int i = 0; i < objects->size(); i++) {
            std::cout << "Draw object!" << std::endl;
            Object *o = (*objects)[i];
            o->draw(shader);
        }
    }
    //    glutSwapBuffers();
}

void onChangeSize(int w, int h) {
    glViewport(0, 0, w, h);
}

void initGLUT(int *argc, const char** argv, int width, int height) {
    glutInit(argc, (char**) argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutCreateWindow("RemoteRenderer");
    glutHideWindow();

    //    glutReshapeFunc(onChangeSize);
    //    glutDisplayFunc(displayFrame);
    //    glutIdleFunc(onIdle);
}

void initGLEW() {
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "%s\n", glewGetErrorString(err));
        exit(1);
    }
}

Shader *setupShaders() {
    std::string v = "vertex.txt";
    std::string f = "fragment.txt";
    Shader *shader = new Shader(v, "", f);
    return shader;
}

void initOpenGL() {
    setupShaders();
    glEnable(GL_DEPTH_TEST);
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

void saveImage(const char* fileName, float* pixels, int width, int height, int quality) {
    Mat image(width, height, CV_32FC3);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            image.at<Vec3f > (width - x - 1, y)[0] = 255 * pixels[3 * (x * height + y) + 0];
            image.at<Vec3f > (width - x - 1, y)[1] = 255 * pixels[3 * (x * height + y) + 1];
            image.at<Vec3f > (width - x - 1, y)[2] = 255 * pixels[3 * (x * height + y) + 2];
        }
    }
    vector<int> params;
    imwrite(fileName, image);
}

Mat getImage(float* pixels, int width, int height, int quality) {
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

void render(FILE *xmlFileName, FILE **img_file) {
    int argc = 1;
    const char* argv[] = {"renderer"};

    int width = 512;
    int height = 512;

    initGLUT(&argc, argv, width, height);
    initGLEW();
    initOpenGL();

    Shader *shader;
    Scene *scene;

    shader = setupShaders();

    Reader reader(shader);
    reader.loadFile(xmlFileName);
    if (reader.isValid()) {
        printf("Scene is valid. Rendering.\n");
        scene = reader.getScene();
        width = scene->getWidth();
        height = scene->getHeight();
        glutInitWindowSize(width, height);
        glViewport(0, 0, width, height);
        displayFrame(shader, scene, width, height);
    } else {
        printf("Scene is invalid.\n");
    }

    int w, h;
    getViewportSize(&w, &h);
    printf("%d x %d\n", w, h);
    float *pixels = new float[w * h * 3];
    readPixels(pixels, w, h);
    Image img(getImage(pixels, w, h, scene->getQuality()));
    if(img.isValid())
    {
        FILE *f=tmpfile();
        fwrite(img.getDataPtr(), img.size(), sizeof (uchar), f);
        fseek(f, 0, SEEK_SET);
        *img_file=f;
    }
    else
    {
        *img_file=NULL;
    }
}

#endif

