#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec3 o_fragPos;
out vec3 o_normal;
out vec2 o_uv;


layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	vec4 cameraPos;
};

layout (std140, binding = 1) uniform Transform
{
    mat4 transform;
};

void main()
{
	mat4 MVP = (transform * view) * projection;
	gl_Position = vec4(position.xyz, 1.0) * MVP;
	o_fragPos = (vec4(position.xyz, 1.0) * (transform)).xyz;
	o_normal = normal;
	o_uv = uv;
}