#version 120
uniform mat4 MVP;

attribute vec4 Position;
attribute vec2 UV;
attribute float Height;

varying vec3 normal;
varying vec2 uv;
varying float height;
varying vec3 position;

void main() 
{
	uv = UV;
	height = Height;
	position = Position.xyz;
    normal = normalize(Position.xyz);
	gl_Position = MVP * vec4(Position.x, Position.y + Height * 30, Position.z, Position.w);
}