
#ifndef READER_H
#define	READER_H

#include "Scene.h"
#include <tinyxml.h>
#include <iostream>
#include "Shader.h"

class Reader {
public:
    Reader(Shader *shader);
    virtual ~Reader();
    void loadFile(const char *file);

    bool isValid() {
        return valid;
    }

    Scene *getScene() {
        return scene;
    }
private:
    void check();
    void read();
    void loadCube(TiXmlElement *e);
    void loadSphere(TiXmlElement *e);
    bool valid;
    TiXmlDocument *document;
    Scene *scene;
    Shader *shader;
};

#endif	/* READER_H */

