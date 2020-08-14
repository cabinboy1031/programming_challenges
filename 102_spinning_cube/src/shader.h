#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader{
	public:
		Shader(std::string vertex_filepath, std::string fragment_filepath);
		GLuint id() const { return this->program_id; };


	private:
	char* vertex_shader;
	char* fragment_shader;
	GLuint program_id;

	GLuint compile_shader(GLenum shader_type, const char* shader_src);
};
