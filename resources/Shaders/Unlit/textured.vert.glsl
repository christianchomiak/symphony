#version 330 core

uniform mat4 MVP;
//uniform mat4 textureMatrix;

layout(location = 0) in vec3 position;	//object space vertex position
layout(location = 2) in vec2 textureCoordinate;	//per-vertex colour

out Vertex {
	vec2 textureCoordinate;
} OUT;

void main(void) {
	gl_Position = MVP * vec4(position, 1.0);
	//OUT.textureCoordinate = (textureMatrix * vec4(textureCoordinate, 0.0, 1.0)).xy;
	OUT.textureCoordinate = textureCoordinate;
}