/* 
 * File:   Sphere.h
 * Author: deather
 *
 * Created on February 7, 2013, 11:17 PM
 */

#ifndef SPHERE_H
#define	SPHERE_H

#include "Cube.h"
#include <math.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

class Sphere : public Object {
public:
    Sphere(float radius, int longs, int cols);
    Sphere(const Sphere& orig);
    virtual ~Sphere();
    virtual void createBuffers();
    virtual void draw(Shader *shader);
    virtual void setupVao(Shader *shader);
private:
    void createArrays();
    float *v;
    float *n;
    float *c;
    int longs;
    int cols;
    int numV;
    int numI;
    GLuint *indices;
    float theta;
    float phi;
    float radius;
    int count;
};

#endif	/* SPHERE_H */

