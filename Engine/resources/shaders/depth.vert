#version 330 core

uniform mat4 Model;
uniform mat4 VP;


layout(location = 0) in vec3 position;

void main()
{
    gl_Position =  (VP * Model) * vec4(position, 1.0f);
}