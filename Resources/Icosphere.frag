#version 120

uniform vec3 LightDirection;
uniform float Height;
varying vec3 normal;
varying vec2 texCoord;
uniform sampler2D SandTexture;
uniform sampler2D GrassTexture;
varying vec3 position;

void main() 
{
	float diffInt = max(0.0, dot(normalize(normal), -LightDirection)); 

 
	vec4 uvColor = texture2D(SandTexture, texCoord);

	float len = length(position.xyz);

	if(len + 0.25 < Height*2) {
		uvColor = texture2D(SandTexture, texCoord);
	}
	else{ 
		uvColor = texture2D(GrassTexture, texCoord);
	}

	gl_FragColor = uvColor * vec4(diffInt, diffInt, diffInt, 1.0f);
}
