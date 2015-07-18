#version 330

in vec3 _color;
out vec4 outColor;

void main() {
    outColor = vec4(_color, 1.0f);
}