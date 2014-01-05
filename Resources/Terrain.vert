#version 120
uniform mat4 MVP;
attribute vec4 Position;
attribute vec2 UV;
attribute float Height;
varying vec3 normal;
varying vec2 uv;

void main() 
{
	uv = UV;
    normal = normalize(Position.xyz);
	gl_Position = MVP * vec4(Position.x, Position.y + Height * 30, Position.z, Position.w);
}