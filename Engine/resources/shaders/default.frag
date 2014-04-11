#version 330 core

uniform sampler2D textureMap;
uniform sampler2D shadowMap;

in float light;
in vec4 shadowCoord;
in vec2 UV;

out vec3 color;

void main()
{
	float shadow = 1.0;
	float bias = 0.001;
	
	if (shadowCoord.x >= 0 && shadowCoord.y >= 0 && shadowCoord.x <= 1 && shadowCoord.y <= 1){
		float total = 0;
		float count = 0;
		int sampleSize = 1;
		for(float i = -sampleSize; i <= sampleSize; i++)
		{
			for(float j = -sampleSize; j <= sampleSize; j++)
			{
				count++;
				total += texture( shadowMap, shadowCoord.xy + vec2(i / 1024.0, j / 1024.0) ).z < shadowCoord.z - bias ? 0.5 : 1.0;
			}
		}
		float d = total / count;
		shadow = d;
	}else{
		shadow = 1.0;
	}
	
	color = texture(textureMap, UV).rgb * light * shadow;
}
