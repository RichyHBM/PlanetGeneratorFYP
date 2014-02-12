#version 120

uniform vec3 LightDirection;

uniform float GrassHeight;
uniform float DirtHeight;
uniform float SnowHeight;

uniform sampler2D SandTexture;
uniform sampler2D GrassTexture;
uniform sampler2D DirtTexture;
uniform sampler2D SnowTexture;

varying vec3 normal;
varying vec2 texCoord;
varying vec3 position;

void main() 
{
	float diffInt = max(0.0, dot(normalize(normal), -LightDirection)); 

 
	vec4 uvColor = texture2D(SandTexture, texCoord);

	float len = length(position.xyz);

	if(len > SnowHeight) {
		uvColor = texture2D(SnowTexture, texCoord);
	}
	else if(len > DirtHeight) {
		uvColor = texture2D(DirtTexture, texCoord);
	}
	else if(len > GrassHeight) {
		uvColor = texture2D(GrassTexture, texCoord);
	}else{
		uvColor = texture2D(SandTexture, texCoord);
	}	

	gl_FragColor = uvColor * vec4(diffInt, diffInt, diffInt, 1.0f);
}
