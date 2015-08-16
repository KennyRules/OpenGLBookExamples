#pragma once

#include <memory>

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
        ShaderLoader::loadShader(shaderFileName, shaderSource);
        glShaderSource(shader, 1, shaderSource, NULL);
        glCompileShader(shader);

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