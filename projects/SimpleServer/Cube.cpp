#include "Cube.h"

Cube::Cube(float size) {
    this->size = size;
    this->modelMatrix = glm::mat4(1.0);
    createArrays();
}

Cube::Cube(const Cube& orig) {
}

Cube::~Cube() {
    delete[] v;
    delete[] n;
    delete[] c;
}

void Cube::createArrays() {
    const float x = size;

    // front face:
    //    AB
    //    CD
    // back face:
    //    EF
    //    GH

    float q1[] = {
        //        -x, x, x, // A
        //        x, x, x, // B
        //        -x, -x, x, // C
        //        x, -x, x, // D        
        //        -x, x, -x, // E
        //        x, x, -x, // F
        //        -x, -x, -x, // G
        //        x, -x, -x, // H

        // front face
        -x, x, x, // A
        x, x, x, // B
        -x, -x, x, // C
        x, -x, x, // D        
        // right face
        x, x, x, // B
        x, x, -x, // F
        x, -x, x, // D
        x, -x, -x, // H        
        // back face
        x, x, -x, // F
        -x, x, -x, // E
        x, -x, -x, // H
        -x, -x, -x, // G
        // left face
        -x, x, -x, // E
        -x, x, x, // A
        -x, -x, -x, // G
        -x, -x, x, // C
        // top face
        -x, x, -x, // E
        x, x, -x, // F
        -x, x, x, // A
        x, x, x, // B
        // bottom face
        -x, -x, -x, // G
        x, -x, -x, // H
        -x, -x, x, // C
        x, -x, x, // D     
    };
    v = new float[72];
    for (int i = 0; i < 72; i++) {
        v[i] = q1[i];
    }


    float q2[] = {
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,

        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,

        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,

        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,

        1.0, 0.0, 1.0,
        1.0, 0.0, 1.0,
        1.0, 0.0, 1.0,
        1.0, 0.0, 1.0,

        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
    };
    c = new float[72];
    for (int i = 0; i < 72; i++) {
        c[i] = q2[i];
    }
    //    c = b;


    float q3[] = {
        0, 1, 0,
        0, 1, 0,
        0, 1, 0,
        0, 1, 0,

        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,

        0, -1, 0,
        0, -1, 0,
        0, -1, 0,
        0, -1, 0,

        -1, 0, 0,
        -1, 0, 0,
        -1, 0, 0,
        -1, 0, 0,

        0, 1, 0,
        0, 1, 0,
        0, 1, 0,
        0, 1, 0,

        0, -1, 0,
        0, -1, 0,
        0, -1, 0,
        0, -1, 0,
    };
    n = new float[72];
    for (int i = 0; i < 72; i++) {
        n[i] = q1[i];
    }
    //    n = d;

    count = 36;
    GLuint tmp[] = {0, 1, 2, 0, 2, 3,};
    indices = new GLuint[36];
    for (int i = 0; i < 6; i++) {
        int o = i * 4;
        indices[i * 6 + 0] = o;
        indices[i * 6 + 1] = o + 1;
        indices[i * 6 + 2] = o + 2;
        indices[i * 6 + 3] = o + 1;
        indices[i * 6 + 4] = o + 2;
        indices[i * 6 + 5] = o + 3;
    }
}

void Cube::createBuffers() {
    const int count = 72;
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof (GLuint), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint) 0);
}

void Cube::draw(Shader *shader) {
    glUniformMatrix4fv(shader->getModelMatrixUniform(), 1, false, glm::value_ptr(modelMatrix));

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glVertexAttribPointer(shader->getVertexAttribute(), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
    glVertexAttribPointer(shader->getColorAttribute(), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
    glVertexAttribPointer(shader->getNormalAttribute(), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
}

void Cube::setupVao(Shader* shader) {
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