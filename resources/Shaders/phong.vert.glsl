#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
//uniform mat4 textureMatrix;

layout(location = 0) in vec3 position;	//object space vertex position
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 textureCoordinate;	//per-vertex colour
layout(location = 3) in vec3 normal;

out Vertex {
	vec3 position;
	vec4 color;
	vec2 textureCoordinate;
	vec3 normal;
} OUT;

void main(void) {
    gl_Position = projectionMatrix * viewMatrix *  modelMatrix * vec4(position, 1.0f);
    OUT.position = vec3(modelMatrix * vec4(position, 1.0f));

	//TO-DO: This is *very* costly, do it once in the CPU 
    OUT.normal = mat3(transpose(inverse(modelMatrix))) * normal;
    
	OUT.textureCoordinate = textureCoordinate;
	OUT.color = vec4(color, 1.0f);
}