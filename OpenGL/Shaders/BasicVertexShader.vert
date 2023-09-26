#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec4 o_fragPos;
out vec3 o_normal;
out vec2 o_uv;
out vec4 FragPosLightSpace;


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

const int MAXNUMBEROFLIGHTS = 6;
layout (std140, binding = 3) uniform ShadowData
{
    vec4 lightPos[MAXNUMBEROFLIGHTS];//4:th element is what type of light it is
	vec4 lightColors[MAXNUMBEROFLIGHTS];//4:th element is how hard the shadows should be
	mat4 lightViewProjection[MAXNUMBEROFLIGHTS];
	int nrOfLight;
};

void main()
{
	mat4 MVP = (transform * view) * projection;
	gl_Position = vec4(position.xyz, 1.0) * MVP;
	o_fragPos = (vec4(position.xyz, 1.0) * (transform));
	o_normal = normal;
	o_uv = uv;
	FragPosLightSpace = lightViewProjection[0] * vec4(o_fragPos.xyz, 1);
}