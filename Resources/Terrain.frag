#version 120
varying vec3 normal;

void main() 
{
	gl_FragColor = (vec4( normal.xyz, 1.0 ) + vec4(1,1,1,1) ) * 0.5;
}