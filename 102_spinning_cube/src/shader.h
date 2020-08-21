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
  Shader(); // basic shader constructor
	Shader(std::string vertex_filepath, std::string fragment_filepath); // Full load using two filepaths

	GLuint id() const { return this->program_id; }; //program_id accessor

  GLuint load(std::string filepath, GLenum shader_type); //load and compile shader from file, overwrites the shader assigned to shader_type if already assigned. Returns compiled shader id
  GLuint load(GLuint shader_id, GLenum shader_type); // Adds already exsting shader to shaders_id, overwrites the shader assigned to shader_type if already assigned. Returns shader id

  void generate_program(); //Finalize the program. It will be ready to use after calling this.
private:
	GLuint program_id; // Final shader program id. Argument for glUseProgram().
  std::map<GLenum, GLuint> shaders_id;

  std::string load_file(std::string shader_filepath);
	GLuint compile(GLenum shader_type, const char* shader_src);
  void attach(); 
  void attach(GLuint shader_id);
  void link();

  void debug_shader(GLuint shader_id);
  void debug_program();
	void _print_shader_info_log(GLuint shader_bin);
	void _print_program_info_log(GLuint program_id);
};
