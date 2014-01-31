#version 120

uniform vec3 LightDirection;
varying vec3 normal;
varying vec2 texCoord;
uniform sampler2D Texture;

void main() 
{
	float diffInt = max(0.0, dot(normalize(normal), -LightDirection)); 
	vec4 uvColor = texture2D(Texture, texCoord); 
	gl_FragColor = uvColor * vec4(diffInt, diffInt, diffInt, 1.0f);
}
