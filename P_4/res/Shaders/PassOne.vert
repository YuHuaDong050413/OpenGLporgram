#version 430 core
layout(location = 0) in vec3 aPos;

uniform mat4 mvp_shadow;

void main()
{
    gl_Position = mvp_shadow * vec4(aPos, 1.0);
}