#version 330 core

uniform sampler2D textSampler;

in float light;

in vec3 pos;
in vec2 UV;

out vec3 color;

void main()
{
	color = texture(textSampler, UV).rgb * light;
	//color = vec3(0.0f, 1.0f, 0.0f) * light;
}

