#version 330 core

in vec2 textureCoordinates;
out vec4 color;

uniform sampler2D screenTexture;

void main(void)
{
  //Normal
	color = texture(screenTexture, textureCoordinates);
  return;
  
  //Invert color
  color = vec4(vec3(1.0 - texture(screenTexture, textureCoordinates)), 1.0);
  //return;
  
  //Grayscale  
  color = texture(screenTexture, textureCoordinates);
  float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
  color = vec4(average, average, average, 1.0);
}
