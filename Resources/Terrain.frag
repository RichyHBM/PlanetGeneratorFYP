#version 120
#define IMG_SIZE 256.0
#define TEXTURE_SIZE 64.0
#define TEXTURES_PER_IMAGE 4.0

varying vec3 normal;
uniform sampler2D TerrainTexture;
varying vec2 uv;
varying float height;
varying vec3 position;

float rand(vec2 co)
{
    float a = 12.9898;
    float b = 78.233;
    float c = 43758.5453;
    float dt = dot(co.xy ,vec2(a,b));
    float sn = mod(dt,3.14);
    return fract(sin(sn) * c);
}

void main() 
{

	float SNOW_ALT = 5.0;
    float SAND_ALT = -0.2 + rand(position.xz) * 0.05;
    float DIRT_ALT = 3.0;



	vec2 actualUV = uv;
	actualUV.y = ((uv.y * TEXTURE_SIZE) / IMG_SIZE);

	if(height < SAND_ALT){//sand
		actualUV.x = 0.75 + ((uv.x * TEXTURE_SIZE) / IMG_SIZE);
	}
	else if(height > SNOW_ALT){//snow
		actualUV.x = 0.5 + ((uv.x * TEXTURE_SIZE) / IMG_SIZE);
	}
	else if(height > DIRT_ALT){//dirt
		actualUV.x = ((uv.x * TEXTURE_SIZE) / IMG_SIZE);
	}
	else{//grass
		actualUV.x = 0.25 + ((uv.x * TEXTURE_SIZE) / IMG_SIZE);
	}



	gl_FragColor = texture2D(TerrainTexture, actualUV);
}