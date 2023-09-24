#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

const int MAXNUMBEROFLIGHTS = 6;

layout (std140, binding = 5) uniform LightData
{
    mat4 lightViewProj;
};

layout (std140, binding = 1) uniform Transform
{
    mat4 transform;
};

void main()
{
	gl_Position = vec4(position.xyz, 1.0) * lightViewProj;
}