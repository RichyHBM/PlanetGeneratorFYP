#version 120
#define IMG_SIZE 256.0
#define TEXTURE_SIZE 64.0
#define TEXTURES_PER_IMAGE 4.0

uniform sampler2D TerrainTexture;

varying vec2 uv;
varying float height;

void main() 
{

	float SNOW_ALT = 5.0;
    float SAND_ALT = -0.2;
    float DIRT_ALT = 3.0;

	vec2 actualUV = uv;

	if(height < SAND_ALT){
		actualUV.x = 0.75 + ((uv.x * TEXTURE_SIZE) / IMG_SIZE);
	}
	else if(height > SNOW_ALT){
		actualUV.x = 0.5 + ((uv.x * TEXTURE_SIZE) / IMG_SIZE);
	}
	else if(height > DIRT_ALT){
		actualUV.x = ((uv.x * TEXTURE_SIZE) / IMG_SIZE);
	}
	else{
		actualUV.x = 0.25 + ((uv.x * TEXTURE_SIZE) / IMG_SIZE);
	}

	gl_FragColor = texture2D(TerrainTexture, actualUV);
}
