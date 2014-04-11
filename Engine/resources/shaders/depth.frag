#version 330 core

layout(location = 0) out float fragdepth;
 

void main()
{
	fragdepth = gl_FragCoord.z;
}
