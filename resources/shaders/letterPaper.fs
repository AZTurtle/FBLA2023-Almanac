#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform vec3 color;

uniform sampler2D tex;

void main()
{
    FragColor = (texture2D(tex, UV) * vec4(color, 1.0f));
}