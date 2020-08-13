#include "shader.h"

Shader::Shader(std::string vertex_filepath, std::string fragment_filepath){
	std::string shader_path = "./shader/";

	std::vector<std::string> vertex_source;
	std::vector<std::string> fragment_source;

	std::ifstream file;
	std::cout << shader_path << vertex_filepath << std::endl;

	file.open(shader_path + vertex_filepath);
	if(!file.is_open()){
		std::cerr << "File not found!" << std::endl;
	}

  std::string buffer;
	while(file.peek() != EOF){
		std::getline(file, buffer);
		if(buffer == ""){
			continue;
		}
		vertex_source.push_back(buffer);
	  std::cout << buffer << std::endl;
	} 

	file.close();
}

GLuint Shader::compile_shader(GLenum shader_type, char* shader_src){
		GLuint shader_bin = glCreateShader(shader_type);
		glShaderSource(shader_bin, 1, &shader_src,NULL);
		glCompileShader(shader_bin);

		return shader_bin;
}
