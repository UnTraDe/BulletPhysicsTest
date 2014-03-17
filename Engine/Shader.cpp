#include "Shader.h"


Shader::Shader()
{
    
}

Shader::Shader(const char* pathVertex, const char* pathGeometry, const char* pathFragment)
{
	LoadFromFile(pathVertex, pathGeometry, pathFragment);
}

bool Shader::LoadFromFile(const char *pathVertex, const char *pathGeometry, const char *pathFragment)
{
    mVertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
	if (pathGeometry)
		mGeometryShaderObj = glCreateShader(GL_GEOMETRY_SHADER);
    mFragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);

    mProgram = glCreateProgram();

    std::ifstream fileVer;
	std::ifstream fileGeo;
    std::ifstream fileFrag;

    fileVer.open(pathVertex);
    if(fileVer.is_open())
    {
        std::string buffer;

        while(fileVer.good())
        {
            std::getline(fileVer, buffer);
            mVertexSource.append(buffer + "\n");
            
        }

        fileVer.close();
    }
    else
    {
        std::cout << "Cannot open shader file: " << pathVertex << std::endl;
        return false;
    }

	if (pathGeometry){
		fileGeo.open(pathGeometry);
		if (fileGeo.is_open())
		{
			std::string buffer;

			while (fileGeo.good())
			{
				std::getline(fileGeo, buffer);
				mGeometrySource.append(buffer + "\n");

			}

			fileGeo.close();
		}
		else
		{
			std::cout << "Cannot open shader file: " << pathGeometry << std::endl;
			return false;
		}
	}

    fileFrag.open(pathFragment);
    if(fileFrag.is_open())
    {
        std::string buffer;

        while(fileFrag.good())
        {
            getline(fileFrag, buffer);
            mFragmentSource.append(buffer + "\n");
        }
        
        fileFrag.close();
    }
    else
    {
        std::cout << "Cannot open shader file: " << pathFragment << std::endl;
        return false;
    }

    const char *vP = mVertexSource.c_str();
	const char *vG = pathGeometry ? mGeometrySource.c_str() : NULL;
    const char *vF = mFragmentSource.c_str();

    glShaderSource(mVertexShaderObj, 1, &vP, NULL);
	if (pathGeometry)
		glShaderSource(mGeometryShaderObj, 1, &vG, NULL);
    glShaderSource(mFragmentShaderObj, 1, &vF, NULL);

	//assert(mVertexShaderObj != 4);

    glCompileShader(mVertexShaderObj);

    GLint Result;
    GLint InfoLogLength;

    glGetShaderiv(mFragmentShaderObj, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(mFragmentShaderObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(mFragmentShaderObj, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	if (pathGeometry){
		glCompileShader(mGeometryShaderObj);
		glGetShaderiv(mFragmentShaderObj, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(mFragmentShaderObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
		std::vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(mFragmentShaderObj, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
	}
    glCompileShader(mFragmentShaderObj);

    glAttachShader(mProgram, mVertexShaderObj);
	if (pathGeometry)
		glAttachShader(mProgram, mGeometryShaderObj);
    glAttachShader(mProgram, mFragmentShaderObj);

    glLinkProgram(mProgram);

    glDeleteShader(mVertexShaderObj);
	if (pathGeometry)
		glDeleteShader(mGeometryShaderObj);
    glDeleteShader(mFragmentShaderObj);

    return true;
}

void Shader::Bind()
{
    glUseProgram(mProgram);
}

void Shader::Release()
{
    glUseProgram(0);
}

GLuint Shader::GetUniformLocation(const char *name)
{
    return glGetUniformLocation(mProgram, name);
}


