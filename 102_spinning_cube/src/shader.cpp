#include "shader.h"

Shader::Shader() {
  valid_program = false;
}

Shader::Shader(std::string vertex_filepath, std::string fragment_filepath){
  load(vertex_filepath, GL_VERTEX_SHADER);
  load(fragment_filepath, GL_FRAGMENT_SHADER);

  generate_program();
}

std::string Shader::load_file(std::string shader_filepath){
  std::ifstream file;
  std::string shader_source;
  const std::string shader_path = "./shader/";

  file.open(shader_path + shader_filepath);
  if(!file.is_open()){
    std::cerr << "Cannot open " << shader_filepath << "! File not found!" << std::endl;
    return "";
  } else {
    std::stringstream bufStream;
    bufStream << file.rdbuf();
    shader_source = bufStream.str();
    file.close();
  }

  return shader_source;
}

GLuint Shader::load(std::string filepath, GLenum shader_type){
  std::string shader_src = load_file(filepath);
  const char *ptr = shader_src.c_str();

  std::cout << "Compiling shader:" <<  filepath << std::endl;
  GLuint shader_id = compile(shader_type, ptr);
  debug_shader(shader_id);

  shaders_id[shader_type] = shader_id;
  return shader_id;
}

GLuint Shader::load(GLuint shader_id, GLenum shader_type){
  shaders_id[shader_type] = shader_id;
  return shader_id;
}

void Shader::generate_program(){
  program_id = glCreateProgram();
  attach();
  link();
  valid_program = true;
}

GLuint Shader::compile(GLenum shader_type, const char* shader_src){
  GLuint shader_bin = glCreateShader(shader_type);
  glShaderSource(shader_bin, 1, &shader_src,NULL);
  glCompileShader(shader_bin);

  // check for compile errors
  int params = -1;
  glGetShaderiv(shader_bin, GL_COMPILE_STATUS, &params);
  if (GL_TRUE != params) {
    gl_log_err("ERROR: GL shader index %i did not compile\n", shader_bin);
    _print_shader_info_log(shader_bin);
    return 0; // or exit or something
  }

  return shader_bin;
}

void Shader::attach(){
  for(auto& shader : shaders_id){
    attach(shader.second);
  }
}

void Shader::attach(GLuint shader_id){
  glAttachShader(program_id,shader_id);
}

void Shader::link(){
  std::cout << "Linking program" << std::endl;
  glLinkProgram(program_id);
  debug_program();
}

void Shader::debug_shader(GLuint shader_id){
  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Check Vertex Shader
  glGetShaderiv(shader_id , GL_COMPILE_STATUS, &Result);
  glGetShaderiv(shader_id , GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> shader_error(InfoLogLength+1);
    glGetShaderInfoLog(shader_id , InfoLogLength, NULL, &shader_error[0]);
    std::cout <<  &shader_error[0] << std::endl;
  }
}

void Shader::debug_program(){
  GLint Result = GL_FALSE;
  int InfoLogLength;
  int params = -1;

  glGetProgramiv(program_id, GL_LINK_STATUS, &Result);
  glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if ( InfoLogLength > 0 ){
    std::vector<char> program_error(InfoLogLength+1);
    glGetProgramInfoLog(program_id, InfoLogLength, NULL, &program_error[0]);
    std::cout << &program_error[0] << std::endl;
  }

  glGetProgramiv(program_id, GL_LINK_STATUS, &params);
  if (GL_TRUE != params) {
    gl_log_err("ERROR: could not link shader programme GL index %u\n",
               program_id);
    _print_program_info_log(program_id);
    return;
  }
}

void Shader::_print_shader_info_log(GLuint shader_bin) {
  int max_length = 2048;
  int actual_length = 0;
  char shader_log[2048];
  glGetShaderInfoLog(shader_bin, max_length, &actual_length, shader_log);
  gl_log_err("shader info log for GL index %u:\n%s\n", shader_bin, shader_log);
}

void Shader::_print_program_info_log(GLuint program_id){
  int max_length = 2048;
  int actual_length = 0;
  char program_log[2048];
  glGetProgramInfoLog(program_id, max_length, &actual_length, program_log);
  gl_log_err("program info log for GL index %u:\n%s", program_id, program_log);
}
