#version 120

uniform vec3 LightDirection;
uniform vec4 WaterColor;

varying vec4 position;
varying vec3 normal;

void main() 
{
	float diffInt = max(0.0, dot(normalize(normal), -LightDirection)); 
	
	gl_FragColor = WaterColor * vec4(diffInt, diffInt, diffInt, 1);
}
