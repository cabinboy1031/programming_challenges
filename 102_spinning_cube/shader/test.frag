#version 330 core

in vec4 vertexColor;

out vec3 fragColor;

void main(){
	fragColor = abs(vertexColor.xyz);
}
