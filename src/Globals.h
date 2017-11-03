#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace Globals
{
	static std::ostream* logging = &std::cout;
	extern glm::mat4 camera;

	static void initGlobals()
	{
		
	//	camera = glm::rotate(camera, (float)70, glm::vec3(0,0,1));
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