#version 130

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 position;
out vec4 pos;

in vec4 color;
out vec4 fColor;

void main()
{
    mat4 mvp = projection * view * model;
    pos = mvp * vec4(position, 1.0);
    gl_Position = vec4(pos);
    fColor = color;
}