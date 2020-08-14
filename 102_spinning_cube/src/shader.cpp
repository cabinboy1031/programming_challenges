#include "shader.h"

Shader::Shader(std::string vertex_filepath, std::string fragment_filepath){
	std::string shader_path = "./shader/";

	std::string vertex_source;
	std::string fragment_source;

	std::ifstream file;

	file.open(shader_path + vertex_filepath);
	if(!file.is_open()){
		std::cerr << "File not found!" << std::endl;
		return;
	} else {
		std::stringstream bufStream;
		bufStream << file.rdbuf();
		vertex_source = bufStream.str();
	  file.close();
	}

	file.open(shader_path + fragment_filepath);
	if(!file.is_open()){
		std::cerr << "File not found!" << std::endl;
		return;
	} else {
		std::stringstream bufStream;
		bufStream << file.rdbuf();
		fragment_source = bufStream.str();
		file.close();
	}

	char const *vertex_ptr = vertex_source.c_str();
	char const *fragment_ptr = fragment_source.c_str();

	GLint Result = GL_FALSE;
	int InfoLogLength;

	std::cout << "Compiling shader:" <<  vertex_filepath << std::endl;
	GLuint vs = compile_shader(GL_VERTEX_SHADER, &vertex_ptr[0]);

	// Check Vertex Shader
	glGetShaderiv(vs , GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs , GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> vertex_error(InfoLogLength+1);
		glGetShaderInfoLog(vs , InfoLogLength, NULL, &vertex_error[0]);
		std::cout <<  &vertex_error[0] << std::endl;
	}

	std::cout << "Compiling shader:" <<  fragment_filepath << std::endl;
	GLuint fs = compile_shader(GL_FRAGMENT_SHADER, &fragment_ptr[0]);

	// Check Vertex Shader
	glGetShaderiv(fs , GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs , GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> fragment_error(InfoLogLength+1);
		glGetShaderInfoLog(vs , InfoLogLength, NULL, &fragment_error[0]);
		std::cout <<  &fragment_error[0] << std::endl;
	}

	std::cout << "Linking program" << std::endl;
	program_id = glCreateProgram();
	glAttachShader(program_id , fs);
	glAttachShader(program_id , vs);
	glLinkProgram(program_id);

	// Check the program
	glGetProgramiv(program_id, GL_LINK_STATUS, &Result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> program_error(InfoLogLength+1);
		glGetProgramInfoLog(program_id, InfoLogLength, NULL, &program_error[0]);
		std::cout << &program_error[0] << std::endl;
	}
}

GLuint Shader::compile_shader(GLenum shader_type, const char* shader_src){
		GLuint shader_bin = glCreateShader(shader_type);
		glShaderSource(shader_bin, 1, &shader_src,NULL);
		glCompileShader(shader_bin);

		return shader_bin;
}
