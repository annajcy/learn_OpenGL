#version 460 core
out vec4 frag_color;

in vec2 uv;

uniform sampler2D screen_texture_sampler;

uniform vec2 resolution;

void main()
{
	frag_color = texture(screen_texture_sampler, uv);
}