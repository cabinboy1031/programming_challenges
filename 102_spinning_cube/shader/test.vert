#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
  
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
  
out vec4 vertexColor;

void main(){
  // Output position of the vertex, in clip space : MVP * position
  gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	vertexColor = vec4(vertexPosition_modelspace,1.0);
	
}
