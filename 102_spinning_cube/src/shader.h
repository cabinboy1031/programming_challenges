#ifndef SHADER_H
#define SHADER_H
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

enum UniformType {
  GLSL_UNIFORM_1_FLOAT,
  GLSL_UNIFORM_2_FLOAT,
  GLSL_UNIFORM_3_FLOAT,
  GLSL_UNIFORM_4_FLOAT,
  GLSL_UNIFORM_1_INT,
  GLSL_UNIFORM_2_INT,
  GLSL_UNIFORM_3_INT,
  GLSL_UNIFORM_4_INT,
  GLSL_UNIFORM_1_UINT,
  GLSL_UNIFORM_2_UINT,
  GLSL_UNIFORM_3_UINT,
  GLSL_UNIFORM_4_UINT,
  GLSL_UNIFORM_VAR_1_FLOAT,
  GLSL_UNIFORM_VAR_2_FLOAT,
  GLSL_UNIFORM_VAR_3_FLOAT,
  GLSL_UNIFORM_VAR_4_FLOAT,
  GLSL_UNIFORM_VAR_1_INT,
  GLSL_UNIFORM_VAR_2_INT,
  GLSL_UNIFORM_VAR_3_INT,
  GLSL_UNIFORM_VAR_4_INT,
  GLSL_UNIFORM_VAR_1_UINT,
  GLSL_UNIFORM_VAR_2_UINT,
  GLSL_UNIFORM_VAR_3_UINT,
  GLSL_UNIFORM_VAR_4_UINT,
  GLSL_UNIFORM_MATRIX_VAR_2_FLOAT,
  GLSL_UNIFORM_MATRIX_VAR_3_FLOAT,
  GLSL_UNIFORM_MATRIX_VAR_4_FLOAT,
  GLSL_UNIFORM_MATRIX_VAR_2x3_FLOAT,
  GLSL_UNIFORM_MATRIX_VAR_3x2_FLOAT,
  GLSL_UNIFORM_MATRIX_VAR_2x4_FLOAT,
  GLSL_UNIFORM_MATRIX_VAR_4x2_FLOAT,
  GLSL_UNIFORM_MATRIX_VAR_3x4_FLOAT,
  GLSL_UNIFORM_MATRIX_VAR_4x3_FLOAT,
};

struct UniformID {
  GLuint id;
  UniformType type;
};

class Shader{
public:
  Shader(); // basic shader constructor
  Shader(std::string vertex_filepath, std::string fragment_filepath); // Full load using two filepaths

  /** Program id accessor.
   *  Warning: Using an id of a Shader object while valid_program is false will cause undefined behavior.
   */
  GLuint id() const { return this->program_id; }
  UniformID get_uniform(std::string name) {return uniform_id[name];}
  GLuint get_uniform_id(std::string name) { return uniform_id[name].id; }
  UniformType get_uniform_type(std::string name) {return uniform_id[name].type; }
  bool is_valid() { return valid_program; }

  /** Load shader and compile if neccesary.
   * Writes to shader_type. If there is already a shader_id written to shader_type, it will be overwritten.
   */
  GLuint load(std::string filepath, GLenum shader_type); // From file
  GLuint load(GLuint shader_id, GLenum shader_type); // Precompiled shader.

  /** Finalize the program. Shader will be ready to use for drawing after calling.
   * Requires at least one shader to be loaded in the object to work.
   * Sets valid_program to true if successful.
   */
  void generate_program();

  /** Add a known uniform to the shader.
   *  Linking a uniform associates a uniform to a string and type,
   *  lets the program know that a shader uses the uniform as well,
   *  uniform_name MUST be the same as in shader.
   *  type may be optional but preferred for checking.
   *  Requires valid_program to be true to do anything.
   *  Updating a uniform will still have to be done manually through glUniform*() functions.
   */
   void link_uniform(std::string uniform_name, UniformType type);

private:
  bool valid_program;
  GLuint program_id; // Final shader program id. Argument for glUseProgram().
  std::map<GLenum, GLuint> shaders_id;
  std::map<std::string,UniformID> uniform_id; 

  std::string load_file(std::string shader_filepath); // Helper function that returns shader source code
  GLuint compile(GLenum shader_type, const char* shader_src);
  void attach();
  void attach(GLuint shader_id);
  void link();

  void debug_shader(GLuint shader_id);
  void debug_program();
  void _print_shader_info_log(GLuint shader_bin);
  void _print_program_info_log(GLuint program_id);
};
#endif // SHADER_H
