
#include "Reader.h"
#include "Cube.h"

Reader::Reader(Shader *shader) {
    this->shader = shader;
}

void Reader::loadFile(const char *f) {
    this->document = NULL;

    this->document = new TiXmlDocument();
    if (!document->LoadFile(f)) {
        document = NULL;
    }
    check();

    if (valid) {
        read();
    }
}

void Reader::loadFile(FILE *f) {
    this->document = NULL;

    printf("Loading xml...\n");
    this->document = new TiXmlDocument();    
    if (!document->LoadFile(f)) {
    	printf("Couldn't load...\n");
        document = NULL;
    }
    check();

    if (valid) {
        scene = Scene();
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
    float ex=0, ey=0, ez=0;
    float lx=0, ly=0, lz=0;
    ex = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("x")->FirstChild()->Value());
    printf("XXX = %s\n", document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("x")->FirstChild()->Value());
    ey = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("y")->FirstChild()->Value());
    ez = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("eye")->FirstChildElement("z")->FirstChild()->Value());
    lx = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("x")->FirstChild()->Value());
    ly = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("y")->FirstChild()->Value());
    lz = atof(document->FirstChildElement("scene")->FirstChildElement("camera")->FirstChildElement("lookAt")->FirstChildElement("z")->FirstChild()->Value());
    
    this->scene.setEyeX(ex);
    this->scene.setEyeY(ey);
    this->scene.setEyeZ(ez);
    this->scene.setLookAtX(lx);
    this->scene.setLookAtY(ly);
    this->scene.setLookAtZ(lz);
    
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
    float x, y, z;
    float rx, ry, rz, angle;

//    TiXmlElement *location = e->FirstChildElement("location");
//    TiXmlElement *rotation = e->FirstChildElement("rotation");
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

    Cube cube(size);
    printf("Cube constructor OK.\n");
    cube.createBuffers();
    printf("Cube create buffers OK.\n");
    cube.setupVao(shader);
    printf("Cube setup vao OK.\n");
    cube.translate(x, y, z);
    printf("Cube setup translation OK.\n");
    cube.rotate(rx, ry, rz, angle);
    printf("Cube setup rotation OK.\n");
    scene.addObject(&cube);
    printf("Cube added to scene OK.\n");
}

void Reader::loadSphere(TiXmlElement* e) {

}

Reader::~Reader() {
    delete document;
}

