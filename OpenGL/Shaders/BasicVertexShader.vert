#version 420 core

struct vertex{
	vec3 position;
	vec3 normal;
	vec2 uv;
};

layout(location = 0) in vertex vertexInput;

out vec4 CPosition;


layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

//layout (std140, binding = 1) uniform Transform
//{
//    mat4 transform;
//};

void main()
{
	mat4 MVP = (view) * projection;
	gl_Position = vec4(vertexInput.position.xyz, 1.0) * MVP;
	CPosition = vec4(vertexInput.position.xyz, 1.0);
	
}