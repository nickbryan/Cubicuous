#version 330

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
in vec3 position;
in vec3 color;
out vec3 _color;

void main() {
    gl_Position = projection  * view * model * vec4(position, 1.0);
    _color = color;
}