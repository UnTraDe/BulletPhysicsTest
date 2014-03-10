#version 330 core

uniform vec3 normalColor;

in float light;

out vec3 color;

void main()
{
	color = normalColor * light;
}
