#include <iostream>
#include "Debugger.h"

void GLClearError()
{
	while( glGetError() != GL_NO_ERROR );
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while( GLenum error = glGetError() ) // not zero, not false
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function
			<< " " << file << ": " << line << std::endl;
		return false;
	}
	return false;
}
