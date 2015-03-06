#version 150

in vec4 vPosition;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection*view*vPosition;
}