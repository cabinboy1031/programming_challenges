#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "logging.h"

class Shader{
	public:
		Shader(std::string vertex_filepath, std::string fragment_filepath);
		GLuint id() const { return this->program_id; };


	private:
	char* vertex_shader;
	char* fragment_shader;
	GLuint program_id;

	GLuint compile_shader(GLenum shader_type, const char* shader_src);
	void _print_shader_info_log(GLuint shader_bin);
	void _print_program_info_log(GLuint program_id);
};

