#version 330 core

layout (location = 0) in vec3 vertexPosition_modelspace;

void main(){
gl_Position.xyz = vertexPosition_modelspace;
gl_position.w = 1.0;
}
