#include <iostream>
#include <time.h>
#include <stdarg.h>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


// Basic logging
bool restart_gl_log();
bool gl_log(const char* message, ...);
bool gl_log_err(const char* messae, ...);

// error callback
void glfw_error_callback(int error, const char* description);

//parameters
void log_gl_params();
