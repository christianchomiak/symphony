#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float nearPlane;
uniform float farPlane;

layout(location = 0) in vec3 position;

out Frustum {
	float near;
  float far;
} OUT;

void main(void) {
    gl_Position = projectionMatrix * viewMatrix *  modelMatrix * vec4(position, 1.0f);
    OUT.near = nearPlane;
    OUT.far = farPlane;
}