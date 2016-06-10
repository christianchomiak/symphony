#version 330 core

in Frustum {
	float near;
  float far;
} IN;

out vec4 outputColor;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * IN.near * IN.far) / (IN.far + IN.near - z * (IN.far - IN.near));	
}
  
void main()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / IN.far; // divide by far for demonstration
  outputColor = vec4(vec3(depth), 1.0f);
} 