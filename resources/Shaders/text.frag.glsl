#version 330 core

uniform sampler2D text;
uniform vec4 foregroundColor;
uniform vec4 backgroundColor;

in vec2 textureCoordinates;

out vec4 color;

void main()
{
    float alpha = texture(text, textureCoordinates).r;
    if (alpha > 0.0)
    {
        vec4 sampled = vec4(1.0, 1.0, 1.0, alpha);
        color = foregroundColor * sampled;
    }
    else
    {
        color = backgroundColor;
    }
}
