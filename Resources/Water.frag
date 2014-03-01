#version 120

#define waterTransparencyDistance 60
#define waterLightBounce 0.6

uniform vec3 LookDirection;
uniform vec3 LightDirection;
uniform vec4 WaterColor;

varying vec4 position;
varying vec3 normal;
varying float distance;

void main() 
{
	vec3 lightReflection = normalize( reflect(LightDirection, normal) );

	float diffInt = max(0.0, dot(normalize(normal), -LightDirection)); 

	float accumulator = clamp( -dot(lightReflection, normalize(LookDirection) ), 0, waterLightBounce);

	float waterTransparency = clamp( (distance / waterTransparencyDistance), 0, 1);

	vec4 waterColor = WaterColor;
	waterColor.a = max(WaterColor.a, waterTransparency);

	gl_FragColor = (waterColor * vec4(diffInt, diffInt, diffInt, 1)) + vec4(accumulator,accumulator,accumulator,0.0f);
}
