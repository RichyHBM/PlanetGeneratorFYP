#version 120

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 NormalMat;

uniform float SinNumber;
uniform float WaveSize;

attribute vec4 Position;
attribute vec3 Normal;

varying vec4 position;
varying vec3 normal;
varying float distance;


void main()
{

	position = Position;
	vec4 pos = Position + (vec4(WaveSize) * sin(SinNumber + Position.y) );

	normal = normalize(( NormalMat * vec4(Normal, 0.0) ).xyz); 
	distance = length( (MV * pos).xyz );
	gl_Position = (MVP * pos);
}
