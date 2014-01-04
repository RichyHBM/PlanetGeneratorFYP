#version 120
uniform mat4 MVP;
uniform float Radius;
uniform float HeightTimes;
attribute vec4 Position;
attribute vec3 Normal;
attribute vec4 Height;
varying vec3 normal;

void main() 
{
    normal = Normal;

    vec4 origin = vec4(0,0,0,1);
	float radius = Radius + Height.w * HeightTimes;
	vec4 delta = Position - origin;

	vec4 mappedPos = origin + (normalize(delta) * radius);
	gl_Position = MVP * mappedPos;
}