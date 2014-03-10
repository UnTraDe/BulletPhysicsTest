#version 330 core
uniform float ambient = 0.5;
uniform vec3 lightDir = vec3(1.0f, -3.0f, 2.0f);

uniform mat4 Model;
uniform mat4 VP;
uniform mat4 InversedTransform;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out float light;

void main()
{
    gl_Position =  (VP * Model) * vec4(position, 1.0f);

	vec3 normalizedTransformedNormal = normalize((InversedTransform * Model * vec4(normal, 1.0f)).xyz);
	float diffuseIntensity = dot(normalizedTransformedNormal, normalize(-lightDir));
	light = clamp(ambient + diffuseIntensity * (1-ambient), 0, 1);
}