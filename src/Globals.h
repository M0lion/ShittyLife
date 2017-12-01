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
	extern glm::mat4 camera;

	const static std::string shaderFolder = "../shaders/";

	inline static void initGlobals()
	{
		
		camera = glm::perspective(.78f, 800.0f/400.0f, 0.1f, 1000.0f);
		camera *= glm::rotate(3.14f, glm::vec3(0.0f, 1.0f, 0.0f));
		camera *= glm::translate(glm::vec3(0.0f,0.0f,5.0f));

		*logging << glm::to_string(camera) << "\n";
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