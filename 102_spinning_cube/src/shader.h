#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "logging.h"

class Shader{
public:
  Shader();
	Shader(std::string vertex_filepath, std::string fragment_filepath);

	GLuint id() const { return this->program_id; };

  std::string load_file(std::string shader_filepath);

  GLuint load(std::string filepath, GLenum shader_type);
  GLuint load(GLuint shader_id, GLenum shader_type);

	GLuint compile(GLenum shader_type, const char* shader_src);
  void attach(GLuint shader_id);
  void link();

private:
	GLuint program_id;
  std::map<GLenum, GLuint> shaders_id;

  void debug_shader(GLuint shader_id);
  void debug_program();
	void _print_shader_info_log(GLuint shader_bin);
	void _print_program_info_log(GLuint program_id);
};
