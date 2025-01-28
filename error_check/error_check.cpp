#include "error_check.h"

void check_error() {
	GLenum error_code = glGetError();
	std::string error;
	if (error_code != GL_NO_ERROR) {
		switch (error_code)
		{
			case GL_INVALID_ENUM: error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:  error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION: error = "INVALID_OPERATION"; break;
			case GL_OUT_OF_MEMORY: error = "OUT OF MEMORY"; break;
			default:
				error = "UNKNOWN";
				break;
		}
		std::cout << error << std::endl;

		assert(false);
	}
}
