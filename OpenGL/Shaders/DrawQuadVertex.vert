#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec2 o_uv;

void main()
{
	gl_Position = vec4(position.xyz, 1.0);
	o_uv = uv;
}