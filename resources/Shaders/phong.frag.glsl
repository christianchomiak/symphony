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
	int type;	// '<0': PointLight, '==0': Directional, '>0': Spotlight 

	vec3 position;
	vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	//Only used by pointlights
	float constant;
    float linear;
    float quadratic;

	//Only used by spotlights
	float cutOff;
	float outerCutOff;
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
	float intensity = 1.0;

    // Ambient
    vec3 ambient = light.ambient * material.ambient * vec3(texture(diffuseTexture, IN.textureCoordinate));
 
    // Diffuse 
    vec3 norm = normalize(IN.normal);

	vec3 lightDir;
	if (light.type == 0)
	{
		lightDir = normalize(-light.direction);
	}
	else if (light.type < 0)
	{
		lightDir = normalize(light.position - IN.position);
	}
	else
	{
		//SPOTLIGHT
		lightDir = normalize(light.position - IN.position);

		// Spotlight (soft edges)
		float theta = dot(lightDir, normalize(-light.direction)); 
		float epsilon = (light.cutOff - light.outerCutOff);
		intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	}

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse * vec3(texture(diffuseTexture, IN.textureCoordinate));      

    // Specular
    vec3 viewDir = normalize(cameraPosition - IN.position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular; // * vec3(texture(material.specular, IN.textureCoordinate));  

	if (light.type != 0) //PointLight
	{
		float distance    = length(light.position - IN.position);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

		ambient  *= attenuation;  
		diffuse  *= attenuation;
		specular *= attenuation;   
	}
	
	diffuse  *= intensity;
	specular *= intensity;

    color = vec4(ambient + diffuse + specular, 1.0);  
} 