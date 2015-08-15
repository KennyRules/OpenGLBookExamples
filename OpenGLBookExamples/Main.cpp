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
        GLuint vertex_shader;
        GLuint tess_control_shader;
		GLuint tess_eval_shader;
		GLuint geom_shader;
		GLuint fragment_shader;
        GLuint program;

		int result = 0;
        /*
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		static GLchar * vertex_shader_source[] = { "" };
		result = ShaderLoader::loadShader("VertexShader.vert", vertex_shader_source);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
        glCompileShader(vertex_shader);
        */

        Shader vertShader(GL_VERTEX_SHADER, "VertexShader.vert");

		float shaderType = GL_TESS_CONTROL_SHADER;
		tess_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		static GLchar * tess_control_source[] = { "" };
		result = ShaderLoader::loadShader("TessControlShader.glsl", tess_control_source);
		glShaderSource(tess_control_shader, 1, tess_control_source, NULL);
		glCompileShader(tess_control_shader);

		tess_eval_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		static GLchar * tess_eval_source[] = { "" };
		result = ShaderLoader::loadShader("TessEvalShader.glsl", tess_eval_source);
		glShaderSource(tess_eval_shader, 1, tess_eval_source, NULL);
		glCompileShader(tess_eval_shader);

		geom_shader = glCreateShader(GL_GEOMETRY_SHADER);
		static GLchar* geom_shader_source[] = { "" };
		result = ShaderLoader::loadShader("GeomShader.glsl", geom_shader_source);
		glShaderSource(geom_shader, 1, geom_shader_source, NULL);
		glCompileShader(geom_shader);

        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		static GLchar * fragment_shader_source[] = { "" };
		result = ShaderLoader::loadShader("FragmentShader.frag", fragment_shader_source);
        glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
        glCompileShader(fragment_shader);

        program = glCreateProgram();
        
		glAttachShader(program, vertShader.getShader());
		glAttachShader(program, tess_control_shader);
		glAttachShader(program, tess_eval_shader);
		glAttachShader(program, geom_shader);
		glAttachShader(program, fragment_shader);
		
        glLinkProgram(program);

        //glDeleteShader(vertex_shader);
		//ShaderLoader::unloadShader(vertex_shader_source);
		glDeleteShader(tess_control_shader);
		ShaderLoader::unloadShader(tess_control_source);
		glDeleteShader(tess_eval_shader);
		ShaderLoader::unloadShader(tess_eval_source);
		glDeleteShader(geom_shader);
		ShaderLoader::unloadShader(geom_shader_source);
        glDeleteShader(fragment_shader);
		ShaderLoader::unloadShader(fragment_shader_source);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPointSize(5.0f);
        return program;
    }
};

DECLARE_MAIN(my_application);