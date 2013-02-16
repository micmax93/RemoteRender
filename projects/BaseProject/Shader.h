#include <string>
#include <GL/glew.h>
#include <stdio.h>

#ifndef SHADER_H
#define	SHADER_H

class Shader {
private:
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint geometryShader;
    GLuint fragmentShader;
    char* readFile(char* fileName);
    GLuint loadShader(GLenum shaderType, char* fileName);
public:
    Shader(std::string vertexShaderFile, std::string geometryShaderFile, std::string fragmentShaderFile);
    ~Shader();
    void bind();
    GLuint getUniformLocation(char* variableName);
    GLuint getAttribLocation(char* variableName);
    GLuint getVertexAttribute();
    GLuint getColorAttribute();
    GLuint getNormalAttribute();
    GLuint getModelMatrixUniform();
    GLuint getViewMatrixUniform();
    GLuint getProjectionMatrixUniform();
};

#endif	/* SHADER_H */

