#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 UV;

uniform mat4 matrix;
uniform mat4 cam;

void main()
{
  gl_Position = cam * matrix * vec4(aPos.x, 0.0f, -aPos.y, 1.0f);
  UV = aUV;
}