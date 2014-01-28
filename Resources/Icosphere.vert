#version 120

uniform mat4 MVP;
uniform mat4 NormalMat;

attribute vec4 Position;
attribute vec3 Normal;

varying vec3 normal;
varying vec3 col;


void main()
{
	col = Position.xyz;
	normal = ( NormalMat * vec4(Normal, 0.0) ).xyz; 
	gl_Position = (MVP * Position);
}
