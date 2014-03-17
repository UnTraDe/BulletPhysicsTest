#version 330 core

uniform float ambient = 0.65;
uniform vec3 lightDir = vec3(1.0f, -3.0f, 2.0f);

layout(triangles) in;
layout (triangle_strip, max_vertices=3) out;

/*out VertexData {
    vec3 light;
} VertexOut;*/

void main()
{
	vec3 normal = vec3(0,-1,0);

	for(int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;

		float diffuseIntensity = dot(normal, normalize(-lightDir));
		//VertexData.light = clamp(ambient + diffuseIntensity * (1-ambient), 0, 1);

		EmitVertex();
	}
}