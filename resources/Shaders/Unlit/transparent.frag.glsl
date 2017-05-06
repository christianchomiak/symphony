#version 330 core

layout(location = 0) out vec4 gl_FragColor;	//fragment shader output

uniform sampler2D textureID;

in Vertex {
	vec2 textureCoordinate;
} IN;

void main(void)
{
  vec4 texColor = texture(textureID, IN.textureCoordinate);
  if (texColor.a == 0.0) discard;
  gl_FragColor = texColor;
}
