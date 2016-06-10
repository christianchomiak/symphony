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
    
out vec4 outputColor;
  
//uniform sampler2D textureID;
uniform vec3 cameraPosition;
uniform Material material;

#define NUMBER_OF_LIGHTS 10
uniform Light lights[NUMBER_OF_LIGHTS];
uniform int numberOfIncomingLights;

//http://theorangeduck.com/page/avoiding-shader-conditionals
float when_eq(int x, int y) {
  return 1.0 - abs(sign(x - y));
}

float when_neq(int x, int y) {
  return abs(sign(x - y));
}

float when_lt(int x, int y) {
  return max(sign(y - x), 0);
}

vec3 ProcessLight(Light light, vec3 normal)
{	
	float intensity = 1.0;

    // Ambient
    vec3 ambient = light.ambient * material.ambient * vec3(texture(diffuseTexture, IN.textureCoordinate));
 
    // Diffuse 

	vec3 lightDir = (-light.direction			 	*  when_eq(light.type, 0)) 
				  + ((light.position - IN.position) * when_neq(light.type, 0));
	lightDir = normalize(lightDir);

	//if (light.type > 0)
	//{
		// Spotlight (soft edges)
		float theta = dot(lightDir, normalize(-light.direction)); 
		float epsilon = (light.cutOff - light.outerCutOff);
		intensity = clamp((theta - light.outerCutOff) / epsilon, when_lt(light.type, 1), 1.0);
	//}

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse * vec3(texture(diffuseTexture, IN.textureCoordinate));      

    // Specular
    vec3 viewDir = normalize(cameraPosition - IN.position);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular; // * vec3(texture(material.specular, IN.textureCoordinate));  

	//if (light.type != 0) //PointLight
	//{
		float distance    = length(light.position - IN.position);
		float attenuation = 1.0 / (when_eq(light.type, 0) +
								   when_neq(light.type, 0) * (light.constant + 
															  light.linear * distance + 
															  light.quadratic * (distance * distance)));		  
		
		//attenuation = (attenuation * when_neq(light.type, 0)) + when_eq(light.type, 0);

		ambient  *= attenuation;
		diffuse  *= attenuation;
		specular *= attenuation;   
	//}

	diffuse  *= intensity;
	specular *= intensity;

    return (ambient + diffuse + specular); 
}

void main()
{	
	vec3 tempColor = vec3(0, 0, 0);
    vec3 normal = normalize(IN.normal);

	for(int i = 0; i < min(numberOfIncomingLights, NUMBER_OF_LIGHTS); ++i)
        tempColor += ProcessLight(lights[i], normal);
 	
    outputColor = vec4(tempColor, 1.0);
} 