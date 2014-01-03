#version 120
uniform mat4 MVP;
attribute vec4 Position;
attribute vec3 Normal;
varying vec3 normal;

void main() 
{
    normal = Normal;

    vec4 origin = vec4(0,0,0,1);
	float radius = 100.0;
	vec4 delta = Position - origin;
	vec4 mappedPos = origin + (normalize(delta) * radius);
	gl_Position = MVP * mappedPos;
}