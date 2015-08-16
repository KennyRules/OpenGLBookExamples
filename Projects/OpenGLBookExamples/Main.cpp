#pragma once
#define WIN32

#include "sb7.h"
#include "vmath.h"
#include "ShaderLoader.h"
#include "Shader.h"

class my_application : public sb7::application
{
public:
    void render(double currentTime)
    {
		const GLfloat color[] = { 0.0f, 0.25f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);

        glUseProgram(rendering_program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void startup()
    {
        rendering_program = compile_shaders();

        GLuint buffer[2];
        GLuint vao;

        static const GLfloat positions[] = { 0.25f, -0.25f, 0.5f, 1.0f,
                                            -0.25f, -0.25f, 0.5f, 1.0f,
                                             0.25f,  0.25f, 0.5f, 1.0f };

        static const GLfloat colors[] = { 1.0, 0.0, 0.0, 1.0,
                                          1.0, 0.0, 0.0, 1.0,
                                          1.0, 0.0, 0.0, 1.0 };
        
        // Create the vertex array object.
        glCreateVertexArrays(1, &vao);

        // Create two buffers.
        glCreateBuffers(2, &buffer[0]);

        // Initialize the first buffer.
        glNamedBufferStorage(buffer[0], sizeof(positions), positions, 0);

        // Bind it to the vertex array - offset zero, stride = sizeof(vec4)
        glVertexArrayVertexBuffer(vao, 0, buffer[0], 0, sizeof(vmath::vec4));

        // Tell OpenGL what the format of the attribute is.
        glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);

        // Tell OpenGL which vertex buffer binding to use for this attribute.
        glVertexArrayAttribBinding(vao, 0, 0);

        // Enable the attribute.
        glEnableVertexArrayAttrib(vao, 0);

        // Perform similar initialization for the second buffer.
        glNamedBufferStorage(buffer[1], sizeof(colors), colors, 0);
        glVertexArrayVertexBuffer(vao, 1, buffer[1], 0, sizeof(vmath::vec4));
        glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vao, 1, 1);
        glEnableVertexArrayAttrib(vao, 1);

        glEnableVertexAttribArray(1);
        glBindVertexArray(vao);
    }

    void shutdown()
    {
        glDeleteProgram(rendering_program);
    }

private:
    GLuint rendering_program;

    void makeShader(GLuint aShaderType, const GLchar* fileName, GLuint& aProgram)
    {
        Shader aShader(aShaderType, fileName);
        glAttachShader(aProgram, aShader.getShader());
    }

    GLuint compile_shaders(void)
    {
        GLuint program;

		int result = 0;

        program = glCreateProgram();

        makeShader(GL_VERTEX_SHADER, "Shaders/VertexShader.vert", program);
        //makeShader(GL_TESS_CONTROL_SHADER, "TessControlShader.glsl", program);
        //makeShader(GL_TESS_EVALUATION_SHADER, "TessEvalShader.glsl", program);
        //makeShader(GL_GEOMETRY_SHADER, "GeomShader.glsl", program);
        makeShader(GL_FRAGMENT_SHADER, "Shaders/FragmentShader.frag", program);

        glLinkProgram(program);
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPointSize(5.0f);
        return program;
    }
};

DECLARE_MAIN(my_application);