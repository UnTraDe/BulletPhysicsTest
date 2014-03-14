#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glew.h>

#include <assert.h>


class Shader 
{
public:
    Shader();
	Shader(const char* pathVertex, const char* pathGeometry, const char* pathFragment);
	bool LoadFromFile(const char *pathVertex, const char *pathGeometry, const char *pathFragment);
    void Bind();
    void Release();
    GLuint GetUniformLocation(const char* name);
	GLuint GetProgram() { return mProgram; };

private:
    GLuint mProgram;
    GLuint mVertexShaderObj;
	GLuint mGeometryShaderObj;
    GLuint mFragmentShaderObj;

    std::string mVertexSource;
	std::string mGeometrySource;
    std::string mFragmentSource;
};
