#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"

Object::Object() {
}

GLuint Object::getIndexBuffer() const {
    return indexBuffer;
}

GLuint Object::getNormalBuffer() const {
    return normalBuffer;
}

GLuint Object::getColorBuffer() const {
    return colorBuffer;
}

GLuint Object::getVertexBuffer() const {
    return vertexBuffer;
}

void Object::setModelMatrix(glm::mat4 modelMatrix) {
    this->modelMatrix = glm::mat4(modelMatrix);
}

void Object::rotate(float x, float y, float z, float angle) {
    modelMatrix = glm::rotate(this->modelMatrix, angle, glm::vec3(x, y, z));
}

void Object::translate(float x, float y, float z) {
    modelMatrix = glm::translate(this->modelMatrix, glm::vec3(x, y, z));
}

Object::Object(const Object& orig) {
    modelMatrix = glm::mat4(1.0);
}

Object::~Object() {
}
