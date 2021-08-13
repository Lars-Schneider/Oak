#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;

uniform mat4 camMatrix;

void main()
{
    gl_Position = camMatrix * vec4(aPos, 1.0);
    ourColor = aColor;
}