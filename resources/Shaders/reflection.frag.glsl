#version 330 core

uniform vec3 cameraPosition;
uniform samplerCube skybox;

in Vertex {
	vec3 position;
	vec3 normal;
} IN;

out vec4 color;

void main()
{
    vec3 incident = normalize(IN.position - cameraPosition);
    vec3 reflection = reflect(incident, normalize(IN.normal));
    color = texture(skybox, reflection);
}
