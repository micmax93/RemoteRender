#ifndef renderer_lock
#define renderer_lock

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
#include <tinyxml.h>
#include "Shader.h"
#include "Object.h"
#include "Cube.h"
#include "Sphere.h"
#include "Reader.h"

using namespace std;
using namespace cv;

class Image {
private:
    bool valid;
    vector<uchar> vbuf;
    int file_size;
    uchar *data;

public:

    Image(Mat img, int quality = 95) {
        vector<int> params;
        params.push_back(CV_IMWRITE_JPEG_QUALITY);
        params.push_back(quality);
        valid = imencode(".jpg", img, vbuf, params);
        file_size = vbuf.size();
        data = vbuf.data();
    }

    ~Image() {
        vbuf.clear();
    }

    bool isValid() {
        return valid;
    }

    uchar *getDataPtr() {
        if (valid) {
            return data;
        } else {
            return NULL;
        }
    }

    int size() {
        return file_size;
    }
};


namespace renderer {

    int windowWidth = 512;
    int windowHeight = 512;

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

    void displayFrame(Scene *scene, Shader *shader) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float cameraAngle = 45.0f;
        glm::mat4 matP = glm::perspective(cameraAngle, (float) windowWidth / (float) windowHeight, 1.0f, 100.0f);
        glm::mat4 matV = glm::lookAt(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        shader->bind();
        glUniformMatrix4fv(shader->getProjectionMatrixUniform(), 1, false, glm::value_ptr(matP));
        glUniformMatrix4fv(shader->getViewMatrixUniform(), 1, false, glm::value_ptr(matV));

        printf("Display frame.!\n");

        //shader->bind();

        //        if (scene != NULL) {
        //            std::vector<Object*> *objects = scene->getObjects();
        //            for (int i = 0; i < objects->size(); i++) {
        //                std::cout << "Draw object!" << std::endl;
        //                Object *o = (*objects)[i];
        //                o->draw(shader);
        //            }
        //        }
        //    glutSwapBuffers();
    }

    void onChangeSize(int w, int h) {
        glViewport(0, 0, w, h);
    }

    void initGLUT() {
        char *myargv [1];
        int myargc = 1;
        myargv [0] = "Myappname";
        
        glutInit(&myargc, myargv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
        glutInitWindowSize(512, 512);
        glutCreateWindow("RemoteRenderer");
        glutShowWindow();
        //        glutHideWindow();
    }

    void initGLEW() {
        GLenum err = glewInit();
        if (GLEW_OK != err) {
            fprintf(stderr, "%s\n", glewGetErrorString(err));
            exit(1);
        }
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

    Image render(FILE *file) {
//        initGLUT();
//        initGLEW();
//        glViewport(0, 0, windowWidth, windowHeight);
        //
        //        std::string v = "vertex.txt";
        //        std::string f = "fragment.txt";
        //        Shader *shader = new Shader(v, "", f);
        //        glEnable(GL_DEPTH_TEST);
        //
        //        Scene *scene = NULL;
        //        
        //        scene = new Scene();
        //        scene->setEyeX(1);
        //        scene->setEyeY(1);
        //        scene->setEyeZ(1);
        //        scene->setLookAtX(0);
        //        scene->setLookAtY(0);
        //        scene->setLookAtZ(0);
        //        
        //        Cube *cube = new Cube(1.0f);
        //        scene->addObject(cube);

        //        Reader reader(shader);
        //        reader.loadFile(file);
        //        if (reader.isValid()) {
        //            printf("Reader is valid.");
        //            scene = reader.getScene();
        //        }
        //        displayFrame(scene, shader);
        //
        int w = 512;
        int h = 512;
        getViewportSize(&w, &h);

        //readPixels(pixels, w, h);

        // tmp
        w = 512;
        h = 512;
        float *pixels = new float[w * h * 3];
        for (int i = 0; i < w * h * 3; i++) {
            pixels[i] = 0.1f;
        }
        Image im = Image(getImage(pixels, w, h), 95);
        return im;
    }

    Image renderImage(FILE* xml_file) {
        return render(xml_file);
    }

};
#endif