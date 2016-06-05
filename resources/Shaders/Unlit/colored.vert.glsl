#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

smooth out vec4 vSmoothColor;
uniform mat4 MVP;

void main()
{
  vSmoothColor = vec4(color, 1);
  gl_Position = MVP * vec4(position, 1);
}