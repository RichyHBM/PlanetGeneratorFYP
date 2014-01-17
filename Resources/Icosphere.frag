#version 120

varying vec3 col;

void main() 
{
	gl_FragColor = vec4(normalize( col.xyz ), 1);
}
