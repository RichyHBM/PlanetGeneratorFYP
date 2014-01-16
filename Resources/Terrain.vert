#version 120

uniform mat4 MVP;

attribute vec4 Position;
attribute vec2 UV;
attribute float Height;

varying vec2 uv;
varying float height;

void main()
{
	uv = UV;
	height = Height;

	gl_Position = (MVP * vec4(Position.x, Height, Position.z, Position.w));
}
