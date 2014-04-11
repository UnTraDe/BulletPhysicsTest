#version 330 core
uniform float ambient = 0.5;
uniform vec3 lightDir = vec3(1.0f, -3.0f, 2.0f);
uniform mat4 biasMatrix = mat4(
0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0
);
uniform mat4 Model;
uniform mat4 VP;
uniform mat4 InversedTransform;
uniform mat4 depthMVP;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

out float light;
out vec4 shadowCoord;
out vec2 UV;

void main()
{
    gl_Position = (VP * Model) * vec4(position, 1.0f);
	shadowCoord = (biasMatrix * depthMVP) * vec4(position, 1.0f);
	UV = texCoords;

	vec3 normalizedTransformedNormal = normalize((InversedTransform * Model * vec4(normal, 1.0f)).xyz);
	float diffuseIntensity = dot(normalizedTransformedNormal, normalize(-lightDir));
	light = clamp(ambient + diffuseIntensity * (1-ambient), 0, 1);
}