#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

class ShaderProgram
{
private:
	GLuint shaderProgram;
	std::vector<GLuint> shaders;

	bool hasVertexShader;
	bool hasFragmentShader;

	GLuint createShader(GLenum type, const GLchar* src);
public:
	ShaderProgram();
	~ShaderProgram();

	bool addShader(GLenum type, const GLchar* src);
	bool use();
	bool link();
	void bindFragDataLocation(GLuint colorNumber, const char * name);
	void vertexAttribPointer(const char* name, GLint size, GLenum type, GLboolean normalized, GLsizei sdtride, const GLvoid* pointer);
	GLint getUniformLocation(const char* name);
};