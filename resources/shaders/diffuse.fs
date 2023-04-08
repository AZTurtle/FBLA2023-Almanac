#version 330 core
out vec4 FragColor;

in vec2 UV;
uniform vec3 color;

uniform sampler2D woodTex;

void main()
{
    FragColor = texture2D(woodTex, UV);
}