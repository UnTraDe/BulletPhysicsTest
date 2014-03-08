#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glew.h>


class Shader 
{
public:
    Shader();
    Shader(const char* pathVertex, const char* pathFragment);
    bool LoadFromFile(const char *pathVertex, const char *pathFragment);
    void Bind();
    void Release();
    GLuint GetUniformLocation(const char* name);

private:
    GLuint mProgram;
    GLuint mVertexShaderObj;
    GLuint mFragmentShaderObj;
    std::string mVertexSource;
    std::string mFragmentSource;
};
