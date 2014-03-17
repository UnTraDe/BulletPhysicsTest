#version 330 core
uniform float ambient = 0.5;
uniform vec3 lightDir = vec3(1.0f, -3.0f, 2.0f);

uniform mat4 MVP;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 UVCords;

out float light;
out vec2 UV;
out vec3 pos;

void main()
{
    gl_Position =  MVP * vec4(position, 1.0f);
	float diffuseIntensity = dot(normal, normalize(-lightDir));
	light = clamp(ambient + diffuseIntensity * (1-ambient), 0, 1);
	UV = UVCords;
	pos = position;
}