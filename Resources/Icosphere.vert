#version 120

uniform mat4 MVP;

attribute vec4 Position;
varying vec3 col;

void main()
{
	col = Position.xyz;
	gl_Position = (MVP * Position);
}
