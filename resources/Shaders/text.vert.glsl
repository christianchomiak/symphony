#version 330 core

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 position;	//object space vertex position
layout(location = 2) in vec2 textureCoordinate;	//per-vertex colour

out vec2 textureCoordinates;

void main()
{
    gl_Position = projectionMatrix * modelMatrix * vec4(position.xy, 0.0, 1.0);
    textureCoordinates = textureCoordinate;
}
