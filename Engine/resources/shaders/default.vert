#version 330 core
uniform float ambient = 0.5;
uniform vec3 lightDir = vec3(1.0f, -3.0f, 2.0f);

uniform mat4 Model;
uniform mat4 VP;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out float light;

void main()
{
    gl_Position =  (VP * Model) * vec4(position, 1.0f);
	light = clamp(ambient + dot(normalize((Model * vec4(normal, 1.0f)).xyz), normalize(-lightDir)) * (1-ambient), 0, 1);
}