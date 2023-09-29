#version 420 core
        
layout(location = 0) out vec4 finalPixel;

//in vec4 o_fragPos;
//in vec2 o_uv;
//in vec3 o_normal;
//in vec3 o_tangent;
//in vec3 o_bitangent;

in vec4 o_fragPos;
in vec2 o_uv;
in vec3 o_normal;
in vec3 o_tangent;
in vec3 o_bitangent;

//texture materials
layout(binding = 0)uniform sampler2D ambientTexture;
layout(binding = 1)uniform sampler2D AOTexture;
layout(binding = 2)uniform sampler2D HeightMapTexture;
layout(binding = 3)uniform sampler2D NormalMapTexture;
layout(binding = 4)uniform sampler2DArray ShadowMaps;

//DEBUG SHIT
const vec3 c_lightColor = vec3(1,1,1);
const vec4 c_lightPos = vec4(0,20,0,0);//w is what kind of light it is

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	vec4 cameraPos;
};

layout (std140, binding = 2) uniform Material
{
    vec4 Ka;//last one is ni;
    vec4 Kd;//last one is d;
    vec4 Ks;//last one is NS;
    vec4 Ke;//last one has materialFlags;
};

const int MAXNUMBEROFLIGHTS = 6;
layout (std140, binding = 3) uniform ShadowData
{
    vec4 lightPos[MAXNUMBEROFLIGHTS];//4:th element is what type of light it is
	vec4 lightColors[MAXNUMBEROFLIGHTS];//4:th element is how hard the shadows should be
	mat4 lightViewProjection[MAXNUMBEROFLIGHTS];
	int nrOfLight;
};

void main(){ 
    finalPixel = vec4(1, o_uv, 1);
    return;
}