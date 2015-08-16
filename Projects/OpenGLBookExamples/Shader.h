#pragma once

#include <iostream>

#include "sb7.h"
#include "ShaderLoader.h"

class Shader
{
private:
    GLuint shader;
    GLuint shaderType;
    const char* shaderFileName;

public:
    Shader(GLuint aShaderType, const GLchar* aFileName) :
        shaderType(aShaderType), shaderFileName(aFileName)
    {
        GLchar* shaderSource[] = { "" };
     
        shader = glCreateShader(shaderType);
        ShaderFileLoader::loadShaderFile(shaderFileName, shaderSource);
        glShaderSource(shader, 1, shaderSource, NULL);
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            std::cout << "Error compiling shader " << aFileName;
        }

        if (*shaderSource != nullptr)
            delete[] * shaderSource;
    }

	GLuint getShader()
    {
        return shader;
    }

	~Shader()
    {
        glDeleteShader(shader);
    }
};