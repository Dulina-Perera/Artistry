#version 450 core

out vec4 FragColor;
uniform vec4 u_BrushColor;

void main()
{
	FragColor = u_BrushColor;
}
