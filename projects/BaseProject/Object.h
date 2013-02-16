#include "Shader.h"
#include <glm/glm.hpp>

#ifndef OBJECT_H
#define	OBJECT_H

class Object {
public:
    Object();
    Object(const Object& orig);
    virtual ~Object();
    virtual void createBuffers() = 0;
    GLuint getIndexBuffer() const;
    GLuint getNormalBuffer() const;
    GLuint getColorBuffer() const;
    GLuint getVertexBuffer() const;
    virtual void draw(Shader *shader) = 0;
    virtual void setupVao(Shader *shader) = 0;
    void setModelMatrix(glm::mat4 modelMatrix);
    void rotate(float x, float y, float z, float angle);
    void translate(float x, float y, float z);
private:
protected:
    GLuint vertexBuffer;
    GLuint colorBuffer;
    GLuint normalBuffer;
    GLuint indexBuffer;
    GLuint vao;
    glm::mat4 modelMatrix;
};

#endif	/* OBJECT_H */

