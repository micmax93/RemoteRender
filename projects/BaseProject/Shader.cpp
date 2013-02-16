#include "Shader.h"

Shader::Shader(std::string vertexShaderFile, std::string geometryShaderFile, std::string fragmentShaderFile) {
    printf("Loading vertex shader...\n");
    char* f = (char*) vertexShaderFile.c_str();
    printf("%s\n", f);
    vertexShader = loadShader(GL_VERTEX_SHADER, f);

    if (geometryShaderFile != "") {
        printf("Loading geometry shader...\n");
        geometryShader = loadShader(GL_GEOMETRY_SHADER, (char*) geometryShaderFile.c_str());
    } else {
        geometryShader = 0;
    }

    printf("Loading fragment shader...\n");
    fragmentShader = loadShader(GL_FRAGMENT_SHADER, (char*) fragmentShaderFile.c_str());

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    if (geometryShaderFile != "") {
        glAttachShader(shaderProgram, geometryShader);
    }
    glLinkProgram(shaderProgram);

    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 1) {
        infoLog = new char[infologLength];
        glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        delete []infoLog;
    }

    printf("Shader program created \n");

    bind();
    printf("%d %d %d\n", getVertexAttribute(), getNormalAttribute(), getColorAttribute());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    printf("done!\n");
}

GLuint Shader::getAttribLocation(char* variableName) {
    return glGetAttribLocation(shaderProgram, variableName);
}

GLuint Shader::getUniformLocation(char* variableName) {
    return glGetUniformLocation(shaderProgram, variableName);
}

GLuint Shader::loadShader(GLenum shaderType, char* fileName) {
    GLuint shader = glCreateShader(shaderType);

    const GLchar* shaderSource = readFile(fileName);

    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    delete []shaderSource;

    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 1) {
        infoLog = new char[infologLength];
        glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
        printf("%s\n", infoLog);
        delete []infoLog;
    }

    return shader;
}

char* Shader::readFile(char* fileName) {
    int filesize;
    FILE *plik;
    char* result;

    plik = fopen(fileName, "r");
    fseek(plik, 0, SEEK_END);
    filesize = ftell(plik);
    fseek(plik, 0, SEEK_SET);
    result = new char[filesize + 1];
    fread(result, 1, filesize, plik);
    result[filesize] = 0;
    fclose(plik);

    return result;
}

void Shader::bind() {
    glUseProgram(shaderProgram);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

Shader::~Shader() {
    glDetachShader(shaderProgram, vertexShader);
    if (geometryShader != 0) glDetachShader(shaderProgram, geometryShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    if (geometryShader != 0) glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);

    glDeleteProgram(shaderProgram);
}

GLuint Shader::getVertexAttribute() {
    return getAttribLocation((char*) "vertex");
}

GLuint Shader::getColorAttribute() {
    return getAttribLocation((char*) "color");
}

GLuint Shader::getNormalAttribute() {
    return getAttribLocation((char*) "normal");
}

GLuint Shader::getModelMatrixUniform() {
    return getUniformLocation((char*) "M");
}

GLuint Shader::getViewMatrixUniform() {
    return getUniformLocation((char*) "V");
}

GLuint Shader::getProjectionMatrixUniform() {
    return getUniformLocation((char*) "P");
}