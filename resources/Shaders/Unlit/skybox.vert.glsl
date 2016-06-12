#version 330 core

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 position;

out vec3 skyboxCoordinate;

void main(void) {
  gl_Position = projectionMatrix * viewMatrix *  vec4(position, 1.0f);
  gl_Position = gl_Position.xyww;
	skyboxCoordinate = position;
}
