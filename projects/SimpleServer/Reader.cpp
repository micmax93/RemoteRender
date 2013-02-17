
#include "Reader.h"
#include "Cube.h"
#include "Sphere.h"

Reader::Reader(Shader *shader) {
    this->shader = shader;
}

void Reader::loadFile(const char *f) {
    this->document = NULL;
    this->scene = NULL;

    this->document = new TiXmlDocument(f);
    if (!document->LoadFile()) {
        document = NULL;
    }
    check();

    if (valid) {
        scene = new Scene();
        read();
    }
}

void Reader::check() {
    if (document == NULL) {
        std::cout << "No document." << std::endl;
        valid = false;
        return;
    }

    if (!document->FirstChildElement("scene")) {
        std::cout << "No scene defined." << std::endl;
        valid = false;
        return;
    }

    if (!document->FirstChildElement("scene")->FirstChildElement("properties")) {
        std::cout << "No properties defined." << std::endl;
        valid = false;
        return;
    }

    if (!document->FirstChildElement("scene")->FirstChildElement("properties")->FirstChildElement("width")
            || !document->FirstChildElement("scene")->FirstChildElement("properties")->FirstChildElement("height")) {
        std::cout << "No width or height specified." << std::endl;
        valid = false;
        return;
    }

    if (!document->FirstChildElement("scene")->FirstChildElement("properties")->FirstChildElement("quality")) {
        std::cout << "No quality specified." << std::endl;
        valid = false;
        return;
    }

    if (!document->FirstChildElement("scene")->FirstChildElement("objects")) {
        std::cout << "No objects defined." << std::endl;
        valid = false;
        return;
    }

    if (!document->FirstChildElement("scene")->FirstChildElement("camera")) {
        std::cout << "No camera defined." << std::endl;
        valid = false;
        return;
    }

    if (!document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")
            || !document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("x")
            || !document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("y")
            || !document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("z")) {
        std::cout << "Wrong camera's eye definition." << std::endl;
        valid = false;
        return;
    }

    if (!document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")
            || !document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("x")
            || !document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("y")
            || !document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("z")) {
        std::cout << "Wrong camera's lookAt definition." << std::endl;
        valid = false;
        return;
    }

    valid = true;
}

void Reader::read() {
    int quality = 50;
    int width = 256;
    int height = 256;
    quality = atoi(document->FirstChildElement("scene")->FirstChildElement("properties")->FirstChildElement("quality")->FirstChild()->Value());
    width = atoi(document->FirstChildElement("scene")->FirstChildElement("properties")->FirstChildElement("width")->FirstChild()->Value());
    height = atoi(document->FirstChildElement("scene")->FirstChildElement("properties")->FirstChildElement("height")->FirstChild()->Value());

    this->scene->setHeight(height);
    this->scene->setWidth(width);
    this->scene->setQuality(quality);

    printf("Width = %d, Height = %d, Quality = %d\n", width, height, quality);

    float ex, ey, ez;
    float lx, ly, lz;
    ex = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("x")->FirstChild()->Value());
    ey = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("y")->FirstChild()->Value());
    ez = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("z")->FirstChild()->Value());
    lx = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("x")->FirstChild()->Value());
    ly = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("y")->FirstChild()->Value());
    lz = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("z")->FirstChild()->Value());
    this->scene->setEyeX(ex);
    this->scene->setEyeY(ey);
    this->scene->setEyeZ(ez);
    this->scene->setLookAtX(lx);
    this->scene->setLookAtY(ly);
    this->scene->setLookAtZ(lz);
    printf("Setting camera: %f %f %f, %f %f %f\n", ex, ey, ez, lx, ly, lz);

    TiXmlElement *o;
    o = document->FirstChildElement("scene")->FirstChildElement("objects")->FirstChildElement();
    while (o != NULL) {
        if (strcmp(o->Value(), "cube") == 0) {
            loadCube(o);
        } else if (strcmp(o->Value(), "sphere") == 0) {
            loadSphere(o);
        }
        o = o->NextSiblingElement();
    }
}

void Reader::loadCube(TiXmlElement* e) {
    float size = 1.0f;
    float r, g, b;
    float x, y, z;
    float rx, ry, rz, angle;

    TiXmlElement *location = e->FirstChildElement("location");
    TiXmlElement *rotation = e->FirstChildElement("rotation");
    if (e->FirstChildElement("size") && e->FirstChildElement("size")->FirstChild()) {
        size = atof(e->FirstChildElement("size")->FirstChild()->Value());
        if (size <= 0.0f) {
            size = 1.0f;
        }
    }
    printf("Size: %f\n", size);

    if (e->FirstChildElement("location") && e->FirstChildElement("location")->FirstChildElement("x") && e->FirstChildElement("location")->FirstChildElement("x")->FirstChild()) {
        x = atof(e->FirstChildElement("location")->FirstChildElement("x")->FirstChild()->Value());
    } else {
        x = 0.0f;
    }
    if (e->FirstChildElement("location") && e->FirstChildElement("location")->FirstChildElement("y") && e->FirstChildElement("location")->FirstChildElement("y")->FirstChild()) {
        y = atof(e->FirstChildElement("location")->FirstChildElement("y")->FirstChild()->Value());
    } else {
        y = 0.0f;
    }
    if (e->FirstChildElement("location") && e->FirstChildElement("location")->FirstChildElement("z") && e->FirstChildElement("location")->FirstChildElement("z")->FirstChild()) {
        z = atof(e->FirstChildElement("location")->FirstChildElement("z")->FirstChild()->Value());
    } else {
        z = 0.0f;
    }
    //    printf("Location: %f %f %f\n", x, y, z);


    if (e->FirstChildElement("rotation") && e->FirstChildElement("rotation")->FirstChildElement("x") && e->FirstChildElement("rotation")->FirstChildElement("x")->FirstChild()) {
        rx = atof(e->FirstChildElement("rotation")->FirstChildElement("x")->FirstChild()->Value());
    } else {
        rx = 0.0f;
    }
    if (e->FirstChildElement("rotation") && e->FirstChildElement("rotation")->FirstChildElement("y") && e->FirstChildElement("rotation")->FirstChildElement("y")->FirstChild()) {
        ry = atof(e->FirstChildElement("rotation")->FirstChildElement("y")->FirstChild()->Value());
    } else {
        ry = 0.0f;
    }
    if (e->FirstChildElement("rotation") && e->FirstChildElement("rotation")->FirstChildElement("z") && e->FirstChildElement("rotation")->FirstChildElement("z")->FirstChild()) {
        rz = atof(e->FirstChildElement("rotation")->FirstChildElement("z")->FirstChild()->Value());
    } else {
        rz = 0.0f;
    }
    if (e->FirstChildElement("rotation") && e->FirstChildElement("rotation")->FirstChildElement("angle") && e->FirstChildElement("rotation")->FirstChildElement("angle")->FirstChild()) {
        angle = atof(e->FirstChildElement("rotation")->FirstChildElement("angle")->FirstChild()->Value());
    } else {
        angle = 0.0f;
    }
    //    printf("Rotation: %f %f %f %f\n", rx, ry, rz, angle);

    Cube *cube = new Cube(size);
    cube->createBuffers();
    cube->setupVao(shader);
    cube->translate(x, y, z);
    const float ALPHA = 0.0001f;
    if ((rx > ALPHA || -rx > ALPHA || ry > ALPHA || -ry > ALPHA || rz > ALPHA || rz > ALPHA) && (angle > ALPHA || -angle > ALPHA)) {
        cube->rotate(rx, ry, rz, angle);
    }
    this->scene->addObject(cube);
}

void Reader::loadSphere(TiXmlElement* e) {
    float size = 1.0f;
    float r, g, b;
    float x, y, z;
    float rx, ry, rz, angle;

    TiXmlElement *location = e->FirstChildElement("location");
    TiXmlElement *rotation = e->FirstChildElement("rotation");
    if (e->FirstChildElement("radius") && e->FirstChildElement("radius")->FirstChild()) {
        size = atof(e->FirstChildElement("radius")->FirstChild()->Value());
        if (size <= 0.0f) {
            size = 1.0f;
        }
    }
    printf("Size: %f\n", size);

    if (e->FirstChildElement("location") && e->FirstChildElement("location")->FirstChildElement("x") && e->FirstChildElement("location")->FirstChildElement("x")->FirstChild()) {
        x = atof(e->FirstChildElement("location")->FirstChildElement("x")->FirstChild()->Value());
    } else {
        x = 0.0f;
    }
    if (e->FirstChildElement("location") && e->FirstChildElement("location")->FirstChildElement("y") && e->FirstChildElement("location")->FirstChildElement("y")->FirstChild()) {
        y = atof(e->FirstChildElement("location")->FirstChildElement("y")->FirstChild()->Value());
    } else {
        y = 0.0f;
    }
    if (e->FirstChildElement("location") && e->FirstChildElement("location")->FirstChildElement("z") && e->FirstChildElement("location")->FirstChildElement("z")->FirstChild()) {
        z = atof(e->FirstChildElement("location")->FirstChildElement("z")->FirstChild()->Value());
    } else {
        z = 0.0f;
    }
    printf("Location: %f %f %f\n", x, y, z);


    if (e->FirstChildElement("rotation") && e->FirstChildElement("rotation")->FirstChildElement("x") && e->FirstChildElement("rotation")->FirstChildElement("x")->FirstChild()) {
        rx = atof(e->FirstChildElement("rotation")->FirstChildElement("x")->FirstChild()->Value());
    } else {
        rx = 0.0f;
    }
    if (e->FirstChildElement("rotation") && e->FirstChildElement("rotation")->FirstChildElement("y") && e->FirstChildElement("rotation")->FirstChildElement("y")->FirstChild()) {
        ry = atof(e->FirstChildElement("rotation")->FirstChildElement("y")->FirstChild()->Value());
    } else {
        ry = 0.0f;
    }
    if (e->FirstChildElement("rotation") && e->FirstChildElement("rotation")->FirstChildElement("z") && e->FirstChildElement("rotation")->FirstChildElement("z")->FirstChild()) {
        rz = atof(e->FirstChildElement("rotation")->FirstChildElement("z")->FirstChild()->Value());
    } else {
        rz = 0.0f;
    }
    if (e->FirstChildElement("rotation") && e->FirstChildElement("rotation")->FirstChildElement("angle") && e->FirstChildElement("rotation")->FirstChildElement("angle")->FirstChild()) {
        angle = atof(e->FirstChildElement("rotation")->FirstChildElement("angle")->FirstChild()->Value());
    } else {
        angle = 0.0f;
    }
    printf("Rotation: %f %f %f %f\n", rx, ry, rz, angle);

    Sphere *sphere = new Sphere(size, 16, 16);
    sphere->createBuffers();
    sphere->setupVao(shader);
    sphere->translate(x, y, z);
    const float ALPHA = 0.0001f;
    if ((rx > ALPHA || -rx > ALPHA || ry > ALPHA || -ry > ALPHA || rz > ALPHA || rz > ALPHA) && (angle > ALPHA || -angle > ALPHA)) {
        sphere->rotate(rx, ry, rz, angle);
    }
    this->scene->addObject(sphere);
}

Reader::~Reader() {
    delete document;
    delete scene;
}

