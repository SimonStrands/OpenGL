#version 420 core

layout(location = 0) out vec4 finalPixel;

in vec4 o_fragPos;
in vec2 o_uv;
in vec3 o_normal;
in float o_lvl;

layout(binding = 0)uniform sampler2D ambientTexture;
layout(binding = 1)uniform sampler2D AOTexture;
layout(binding = 2)uniform sampler2D HeightMapTexture;
layout(binding = 3)uniform sampler2D NormalMapTexture;
layout(binding = 4)uniform sampler2DArray ShadowMaps;

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

uint lowbias32(uint x)
{
    x ^= x >> 16;
    x *= 0x7feb352dU;
    x ^= x >> 15;
    x *= 0x846ca68bU;
    x ^= x >> 16;
    return x;
}

float rand(ivec2 co)
{
    uint seed = co.x * 1000 + co.y * 69;
    uint a = uint(lowbias32(seed));
    float r = (sin((float(a % 1000))) + 1) / 2;
    
    return r;
}

const int nrOfLayers = 100;
const float ph = 1.0/nrOfLayers;
const vec2 size = vec2(1000.0,1000.0);

void main(){    
    vec2 space = vec2(o_uv * size);
    ivec2 co = ivec2(space);
    
    vec2 localSpace = fract(space) * 2 - 1;
    float distanceFromCenter = distance(localSpace, vec2(0,0));
    
    
    float height = rand(co);//random value between 0-1  
    
    //if(height < o_lvl * ph || distanceFromCenter > (height - (o_lvl) * ph) * 1.2)
    if(height < o_lvl * ph)
    {
        discard;
    }
    float green = ph * o_lvl;
    finalPixel = vec4(0,green,0,1);
    
    return;
}