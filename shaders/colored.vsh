#version 130

uniform mat4 camera;

in vec3 position;
out vec4 pos;

in vec4 color;
out vec4 fColor;

void main()
{
    pos = camera * vec4(position, 1.0);
    gl_Position = vec4(pos);
    fColor = color;
}