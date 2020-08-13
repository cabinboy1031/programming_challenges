#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader{
	public:
		Shader(std::string vertex_filepath, std::string fragment_filepath);


	private:
	char* vertex_shader;
	char* fragment_shader;

	GLuint compile_shader(GLenum shader_type, char* shader_src);
};
