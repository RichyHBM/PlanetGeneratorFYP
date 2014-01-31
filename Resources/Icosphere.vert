#version 120

uniform mat4 MVP;
uniform mat4 NormalMat;

attribute vec4 Position;
attribute vec3 Normal;
attribute vec2 UV;

varying vec3 normal;
varying vec2 texCoord;


void main()
{
	texCoord = UV;
	normal = ( NormalMat * vec4(Normal, 0.0) ).xyz; 
	gl_Position = (MVP * Position);
}
