#version 120

uniform vec3 LookDirection;
uniform vec3 LightDirection;
uniform vec4 WaterColor;

varying vec4 position;
varying vec3 normal;

void main() 
{
	vec3 lightReflection = normalize( reflect(LightDirection, normal) );

	float diffInt = max(0.0, dot(normalize(normal), -LightDirection)); 

	float accumulator = clamp( -dot(lightReflection, normalize(LookDirection) ), 0, 1);

	gl_FragColor = (WaterColor * vec4(diffInt, diffInt, diffInt, 1)) + vec4(accumulator,accumulator,accumulator,accumulator);
}
