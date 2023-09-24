#version 420 core
        
layout(location = 0) out vec4 finalPixel;
    
in vec3 o_fragPos;
in vec3 o_normal;
in vec2 o_uv;

//texture materials
uniform sampler2D ambientTexture;
uniform sampler2D AOTexture;
uniform sampler2D HeightMapTexture;
uniform sampler2D NormalMapTexture;

//DEBUG SHIT
const vec3 lightColor = vec3(1,1,1);
const vec4 lightPos = vec4(0,20,0,0);//w is what kind of light it is

layout (std140, binding = 0) uniform Matrices
{
    mat4 projection;
    mat4 view;
	vec4 cameraPos;
};

layout (std140, binding = 2) uniform Material
{
    vec4 Ka;
    vec4 Kd;
    vec4 Ks;
    vec4 Ke;
};

void main(){ 

    vec3 PixelLight = vec3(0,0,0); 
    vec4 color = texture(ambientTexture, o_uv);

    vec3 viewDir = normalize(cameraPos.xyz - o_fragPos);
    vec3 lightDir = normalize(lightPos.xyz - o_fragPos);
    float dist = length(lightPos.xyz - o_fragPos);

    vec3 ambientLight = Ka.xyz * lightColor;

    vec3 defuse_light;
    float ammount_diffuse = max(dot(o_normal, lightDir), 0.0f);
    defuse_light = ammount_diffuse * Kd.xyz * lightColor;

    vec3 reflectDir = reflect(-lightDir, o_normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Ks.w + 0.000001);
    vec3 specular = Ks.xyz * spec;

    PixelLight = clamp(ambientLight + defuse_light, 0.0, 1.0) + specular;


    finalPixel = vec4(PixelLight * color.xyz, color.a);
}