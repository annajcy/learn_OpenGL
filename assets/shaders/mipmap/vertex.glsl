#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 texCoord;

uniform float time;
uniform float speed;

void main()
{
    float scale = 1.0 / (time * speed);
    vec3 pos = aPos * scale;
    gl_Position = vec4(pos, 1.0);
    texCoord = aTexCoord;
}