#version 120
varying vec3 normal;
uniform sampler2D TerrainTexture;
varying vec2 uv;

void main() 
{
	gl_FragColor = texture2D(TerrainTexture, uv);
}