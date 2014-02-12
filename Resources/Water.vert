#version 120

uniform mat4 MVP;
uniform mat4 NormalMat;

uniform float SinNumber;
uniform float WaveSize;

attribute vec4 Position;
attribute vec3 Normal;
attribute vec2 UV;

varying vec4 position;
varying vec3 normal;
varying vec2 texCoord;


void main()
{
	texCoord = UV;
	position = Position;
	vec4 pos = Position + (vec4(WaveSize) * sin(SinNumber + Position.y) );

	normal = normalize(( NormalMat * vec4(Normal, 0.0) ).xyz); 
	gl_Position = (MVP * pos);
}
