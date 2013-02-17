/* 
 * File:   Sphere.cpp
 * Author: deather
 * 
 * Created on February 7, 2013, 11:17 PM
 */

#include "Sphere.h"

void Sphere::createBuffers() {
    const int count = numV * 3;
    const int size = count * sizeof (float);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, v, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, c, GL_STATIC_DRAW);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, n, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, (GLuint) 0);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * numI * sizeof (GLuint), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint) 0);
}

void Sphere::draw(Shader *shader) {
    glUniformMatrix4fv(shader->getModelMatrixUniform(), 1, false, glm::value_ptr(modelMatrix));

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glVertexAttribPointer(shader->getVertexAttribute(), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
    glVertexAttribPointer(shader->getColorAttribute(), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
    glVertexAttribPointer(shader->getNormalAttribute(), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, numI * 3, GL_UNSIGNED_INT, NULL);
}

void Sphere::setupVao(Shader *shader) {
    GLuint attr;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    attr = shader->getVertexAttribute();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(attr, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    attr = shader->getColorAttribute();
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(attr, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    attr = shader->getNormalAttribute();
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(attr, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sphere::createArrays() {
    const float PI = 3.14159265;
    const float TWOPI = PI * 2.0f;

    const float R = radius;
    int num_verts_x = this->longs + 1; // first is replicated
    int num_verts_y = this->cols * 2 - 1;
    int num_tris = (num_verts_x - 1) * (num_verts_y - 1) * 2;
    int num = num_verts_x * num_verts_y;

    this->numI = num_tris;
    this->numV = num;

    this->v = new float[num * 3];
    this->n = new float[num * 3];
    this->c = new float[num * 3];
    this->indices = new GLuint[num_tris * 3];

    int i = 0; // vertex identifier
    int j = 0; // triangle identifier
    for (int a = 0; a < num_verts_x; a++) {
        for (int b = 0; b < num_verts_y; b++) {
            float theta = (TWOPI * (float) a / (float) longs);
            float phi = PI * (float) b / (float) (num_verts_y - 1);


            float cos_phi = cos(phi);
            float sin_phi = sin(phi);
            float cos_theta = cos(theta);
            float sin_theta = sin(theta);

            float x = sin_theta * sin_phi;
            float y = cos_phi;
            float z = cos_theta * sin_phi;

            v[i * 3 + 0] = (float) x * R;
            v[i * 3 + 1] = (float) y * R;
            v[i * 3 + 2] = (float) z * R;

            n[i * 3 + 0] = (float) x;
            n[i * 3 + 1] = (float) y;
            n[i * 3 + 2] = (float) z;

            c[i * 3 + 0] = (float) x;
            c[i * 3 + 1] = (float) y;
            c[i * 3 + 2] = (float) z;

            if (a < num_verts_x - 1 && b < num_verts_y - 1) {
                // 0 1
                // 2 3
                int vert0 = i;
                int vert1 = i + num_verts_y;
                int vert2 = i + 1;
                int vert3 = vert1 + 1;
                indices[j++] = vert0;
                indices[j++] = vert1;
                indices[j++] = vert2;
                indices[j++] = vert1;
                indices[j++] = vert2;
                indices[j++] = vert3;
            }

            i++;
        }
    }
}

Sphere::Sphere(float radius, int longs, int cols) {
    this->modelMatrix = glm::mat4(1.0);
    const float pi = 3.14159265;
    const float twopi = pi * 2.0f;

    if (radius > 0.01f) {
        this->radius = radius;
    } else {
        radius = 1.0f;
    }

    if (longs > 16) {
        this->longs = longs;
    } else {
        this->longs = 16;
    }

    this->theta = twopi / (float) this->longs;

    if (cols > 2) {
        this->cols = cols;
    } else {
        this->cols = 2;
    }

    this->phi = pi / (float) this->cols;

    this->numV = this->longs * this->cols * 2;
    this->numI = this->longs * (this->cols - 1)*2 * 2 * 6;

    this->createArrays();
}

Sphere::Sphere(const Sphere& orig) {
}

Sphere::~Sphere() {
}

