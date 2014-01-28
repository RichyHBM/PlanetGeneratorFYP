#version 120

uniform vec3 LightDirection;
varying vec3 normal;
varying vec3 col;

void main() 
{
	float diffInt = max(0.0, dot(normalize(normal), -LightDirection)); 

	gl_FragColor = vec4(diffInt, diffInt, diffInt, 1.0f);
}
