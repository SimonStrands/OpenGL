#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

out vec4 o_fragPos;
out vec2 o_uv;
out vec3 o_normal;
out float o_lvl;

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

const float layerdiff = 0.01;
const int nrOfLayers = 100;

void main()
{
	mat4 MVP = (transform * view) * projection;
	//may swap positions

	vec4 nposition = vec4(position, 1) + (vec4(-normal, 0) * (gl_InstanceID * layerdiff));
	o_lvl = nrOfLayers - gl_InstanceID;

	gl_Position = nposition * MVP;
	o_fragPos = (nposition * (transform));
	o_normal = normalize((vec4(normal, 0.0) * transform).xyz);
	o_uv = uv;
}