#version 330 core

uniform sampler2D diffuseTexture;

struct Material 
{
    /*sampler2D diffuse;
    sampler2D specular;*/
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    
	float shininess;
};  

struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in Vertex {
	vec3 position;
	vec4 color;
	vec2 textureCoordinate;
	vec3 normal;
} IN;
    
out vec4 color;
  
//uniform sampler2D textureID;
uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * material.ambient * vec3(texture(diffuseTexture, IN.textureCoordinate));
  	
	/*color = vec4(light.ambient, 1.0f);
	return;*/

    // Diffuse 
    vec3 norm = normalize(IN.normal);
    // vec3 lightDir = normalize(light.position - IN.position);
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse * vec3(texture(diffuseTexture, IN.textureCoordinate));  
    
	/*color = vec4(diffuse, 1.0);
	return;*/

    // Specular
    vec3 viewDir = normalize(cameraPosition - IN.position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular; // * vec3(texture(material.specular, IN.textureCoordinate));  

    color = vec4(ambient + diffuse + specular, 1.0f);  
} 