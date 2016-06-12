#version 330 core

uniform mat4 projectionMatrix;

layout (location = 0) in vec4 vertex;

out vec2 textureCoordinates;

void main()
{
    gl_Position = projectionMatrix * vec4(vertex.xy, 0.0, 1.0);
    textureCoordinates = vertex.zw;
}
