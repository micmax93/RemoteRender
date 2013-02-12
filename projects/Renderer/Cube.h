/* 
 * File:   Cube.h
 * Author: deather
 *
 * Created on January 29, 2013, 12:30 AM
 */

#ifndef CUBE_H
#define	CUBE_H

#include "Object.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>


class Cube : public Object{
public:
    Cube(float size);
    Cube(const Cube& orig);
    virtual ~Cube();
    virtual void createBuffers();
    virtual void draw(Shader *shader);
    virtual void setupVao(Shader *shader);
private:
    void createArrays();
    float *v;
    float *n;
    float *c;
    GLuint *indices;
    float size;
    int count;
};

#endif	/* CUBE_H */

