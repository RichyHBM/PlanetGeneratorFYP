#version 120
uniform mat4 MVP;
attribute vec4 Position;
attribute vec3 Normal;
varying vec3 normal;

void main() 
{
    normal = Normal;
    gl_Position =  MVP * Position;
}