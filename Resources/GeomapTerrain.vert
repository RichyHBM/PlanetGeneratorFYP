#version 120

uniform mat4 MVP;
uniform mat4 Model;

attribute vec4 Position;
attribute vec2 UV;

varying vec3 normal;
varying vec2 uv;
varying float height;
varying vec3 position;

#include ./Resources/noise3D.glsl

void main() 
{
	vec3 finalPosition = (Model * Position).xyz;

	uv = UV;
	height = snoise( vec3( finalPosition.x * 0.01, finalPosition.z * 0.01 , 123.0) );
	position = finalPosition.xyz;
    normal = normalize(finalPosition.xyz);

    vec4 pos = Position;
    pos.y = (height - 0.5) * 50;
	gl_Position = (MVP * pos);
}