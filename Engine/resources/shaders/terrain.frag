#version 330 core

uniform sampler2D textSampler;

in float light;
//in vec2 UV;
in vec3 pos;

out vec3 color;

void main()
{
	//color = texture(textSampler, UV).rgb * light;
	color = vec3(0.0f, 1.0f, 0.0f) * light;
}

