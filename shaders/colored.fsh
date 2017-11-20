#version 130

in vec4 pos;
out vec4 outColor;

in vec4 fColor;

void main()
{
    vec4 Pos = pos;

    float n = sqrt((Pos.x*Pos.x)+(Pos.y*pos.y))*10;

    outColor = vec4(tan(n),sin(n),cos(n),1);
    outColor = fColor;
}