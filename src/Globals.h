#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <string>

#include "glm/ext.hpp"

namespace Globals
{
	static std::ostream* logging = &std::cout;
	extern glm::mat4 projectionMatrix;

	static int windowWidth = 800;
	static int windowHeight = 600;

	const static std::string shaderFolder = "../shaders/";

	extern bool keys[GLFW_KEY_LAST];

	static void updateProjection()
	{
		projectionMatrix = glm::perspective(.78f, windowWidth/(float)windowHeight, 0.1f, 1000.0f);
    	glViewport(0,0, windowWidth, windowHeight);
	}

	inline static void initGlobals()
	{		
		updateProjection();
	}

	inline static void checkGLError(char* msg)
	{
		GLenum error = glGetError();
		if (error)
		{
			*logging << "openGL error: " << error << " (" << msg << ")\n";
		}
	}
}