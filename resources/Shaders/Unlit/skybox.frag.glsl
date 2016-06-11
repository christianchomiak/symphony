#version 330 core

out vec4 gl_FragColor;	//fragment shader output

uniform samplerCube skyboxTexture;

in vec3 skyboxCoordinate;

void main(void)
{
  gl_FragColor = texture(skyboxTexture, skyboxCoordinate);
}
