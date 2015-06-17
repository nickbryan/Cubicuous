#version 150 core

in vec3 position;
in vec3 color;

out vec3 Color;

uniform mat4 mvp;

void main()
{
    Color = color;

    gl_Position = mvp * vec4(position, 1.0);
}