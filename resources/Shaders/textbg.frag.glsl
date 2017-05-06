#version 330 core

uniform sampler2D text;
uniform vec4 bgColor;

in vec2 textureCoordinates;

out vec4 color;

void main()
{
    color = bgColor;
}
