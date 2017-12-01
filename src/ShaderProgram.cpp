#include "ShaderProgram.h"

#include "Globals.h"

ShaderProgram::ShaderProgram()
{
	shaderProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
}

bool ShaderProgram::link()
{
	if (!(hasFragmentShader && hasVertexShader))
	{
		*Globals::logging << "ERROR: tried to link shaderProgram without either vertex or fragment shader\n";
		return false;
	}

	glLinkProgram(shaderProgram);
	return true;
}

bool ShaderProgram::use()
{
	if (shaderProgram == -1)
	{
		*Globals::logging << "ERROR: tried to use uninitialized shaderProgram\n";
		return false;
	}
	glUseProgram(shaderProgram);
	return true;
}

bool ShaderProgram::addShader(GLenum type, const GLchar* src)
{
	int shader;
	shaders.push_back(shader = createShader(type, src));
	glAttachShader(shaderProgram, shader);

	if (type == GL_VERTEX_SHADER)
		hasVertexShader = true;
	if (type == GL_FRAGMENT_SHADER)
		hasFragmentShader = true;

	return shader != -1;
}

GLuint ShaderProgram::createShader(GLenum type, const GLchar* src)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);

		*(Globals::logging) << "shader compile errors:\n" << buffer << "\n";

		return -1;
	}

	return shader;
}

void ShaderProgram::bindFragDataLocation(GLuint colorNumber, const char* name)
{
	glBindFragDataLocation(shaderProgram, colorNumber, name);
}

void ShaderProgram::vertexAttribPointer(const char* name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	GLint attribPos = glGetAttribLocation(shaderProgram, name);

	if (attribPos == -1)
	{
		*Globals::logging << "could not find shader attribute \"" << name << "\"\n";
		//throw "could not find shader attribute";
		return;
	}

	glVertexAttribPointer(attribPos, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(attribPos);
}

GLint ShaderProgram::getUniformLocation(const char * name)
{
	GLint location = glGetUniformLocation(shaderProgram, name);
	if (location == -1)
	{
		*Globals::logging << "Couldnt find uniform \"" << name << "\"\n";
	}

	return location;
}
