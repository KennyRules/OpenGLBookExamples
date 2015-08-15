#pragma once
#define WIN32

#include "sb7.h"
#include "ShaderLoader.h"
#include "Shader.h"

class my_application : public sb7::application
{
public:
    void render(double currentTime)
    {
		const GLfloat color[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);

        GLfloat triColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };

        glVertexAttrib4fv(1, triColor);

        glUseProgram(rendering_program);
        glDrawArrays(GL_PATCHES, 0, 3);
    }

    void startup()
    {
        rendering_program = compile_shaders();
        glCreateVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
    }

    void shutdown()
    {
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
        glDeleteVertexArrays(1, &vertex_array_object);
    }

private:
    GLuint rendering_program;
    GLuint vertex_array_object;

    GLuint compile_shaders(void)
    {
        GLuint program;

		int result = 0;

        Shader vertexShader(GL_VERTEX_SHADER, "VertexShader.vert");
        Shader tessControlShader(GL_TESS_CONTROL_SHADER, "TessControlShader.glsl");
        Shader tessEvalShader(GL_TESS_EVALUATION_SHADER, "TessEvalShader.glsl");
        Shader geomShader(GL_GEOMETRY_SHADER, "GeomShader.glsl");
        Shader fragmentShader(GL_FRAGMENT_SHADER, "FragmentShader.frag");

        program = glCreateProgram();
        
		glAttachShader(program, vertexShader.getShader());
		glAttachShader(program, tessControlShader.getShader());
		glAttachShader(program, tessEvalShader.getShader());
		glAttachShader(program, geomShader.getShader());
		glAttachShader(program, fragmentShader.getShader());
		
        glLinkProgram(program);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPointSize(5.0f);
        return program;
    }
};

DECLARE_MAIN(my_application);