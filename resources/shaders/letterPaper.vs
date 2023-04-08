#version 330 core
layout (location = 0) in vec4 aVert;

uniform mat4 camMatrix;
uniform mat4 objMatrix;

out vec2 UV;

void main()
{
  gl_Position = camMatrix * objMatrix * vec4(aVert.x, 0.251f, aVert.y, 1.0f);
  UV = vec2(aVert.z, aVert.w);
}