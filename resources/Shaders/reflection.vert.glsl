#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec3 normal;

out Vertex {
	vec3 position;
	vec3 normal;
} OUT;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    vec4 tempPosition =  modelMatrix * vec4(position, 1.0f);

    OUT.normal = normalize(transpose(inverse(mat3(modelMatrix))) * normalize(normal));
    OUT.position = tempPosition.xyz;

    gl_Position = projectionMatrix * viewMatrix * tempPosition;
}
