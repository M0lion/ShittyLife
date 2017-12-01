#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <string>

namespace Globals
{
	static std::ostream* logging = &std::cout;
	static glm::mat4 camera;
	static glm::mat4 projectionMatrix;

	static int windowWidth = 800;
	static int windowHeight = 600;

	const static std::string shaderFolder = "../shaders/";

	static void updateProjection()
	{
		projectionMatrix = glm::perspective(.78f, windowWidth/(float)windowHeight, 0.1f, 1000.0f);
	}

	static void initGlobals()
	{
		updateProjection();
		camera = glm::perspective(.78f, 800.0f/400.0f, 0.1f, 1000.0f);
		camera *= glm::rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	static void checkGLError(char* msg)
	{
		GLenum error = glGetError();
		if (error)
		{
			*logging << "openGL error: " << error << " (" << msg << ")\n";
		}
	}
}