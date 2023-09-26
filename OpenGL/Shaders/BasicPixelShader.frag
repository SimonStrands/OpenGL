#version 420 core
        
layout(location = 0) out vec4 finalPixel;
    
in vec4 o_fragPos;
in vec3 o_normal;
in vec2 o_uv;
in vec4 FragPosLightSpace;

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
    vec4 Ka;
    vec4 Kd;
    vec4 Ks;
    vec4 Ke;
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
    
    
     vec3 PixelLight = vec3(0,0,0); 
    vec4 color = texture(ambientTexture, o_uv);
    vec3 viewDir = normalize(cameraPos.xyz - o_fragPos.xyz);
    
    for(int i = 0; i < nrOfLight.x; i++){
        
        vec3 lightDir = normalize(lightPos[i].xyz - o_fragPos.xyz);
        float dist = length(lightPos[i].xyz - o_fragPos.xyz);
        
        vec3 ambientLight = Ka.xyz * lightColors[i].xyz;
    
        vec4 shadowHomo = o_fragPos * lightViewProjection[i];
        //vec4 shadowMapCoords = shadowHomo * 0.5 + 0.5;
        vec4 shadowMapCoords = shadowHomo * vec4(0.5, 0.5, 1.0f, 1.0f) + (vec4(0.5f, 0.5f, 0.0f, 0.0f) * shadowHomo.w);
        
        shadowMapCoords.xyz = shadowMapCoords.xyz / shadowMapCoords.w;
        
        float SM = texture(ShadowMaps, vec3(shadowMapCoords.xy, i)).r;
        
        const float bias = 0.0001; // Adjust the bias value as needed
        
        if (SM > shadowMapCoords.z - bias) 
        {
            vec3 defuse_light;
            float ammount_diffuse = max(dot(o_normal, lightDir), 0.0f);
            defuse_light = ammount_diffuse * Kd.xyz * lightColors[i].xyz;
            
            vec3 reflectDir = reflect(-lightDir, o_normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), Ks.w + 0.000001);
            vec3 specular = Ks.xyz * spec;
            
            PixelLight += clamp(ambientLight + defuse_light, 0.0, 1.0) + specular;
        }
        else{
            PixelLight += ambientLight;
        }    
    }
    finalPixel = vec4(PixelLight * color.xyz, color.a);
    

    //vec3 PixelLight = vec3(0,0,0); 
    //vec4 color = texture(ambientTexture, o_uv);
    //
    //vec3 viewDir = normalize(cameraPos.xyz - o_fragPos.xyz);
    //vec3 lightDir = normalize(c_lightPos.xyz - o_fragPos.xyz);
    //float dist = length(c_lightPos.xyz - o_fragPos.xyz);
    //
    //vec3 ambientLight = Ka.xyz * c_lightColor;
    //
    //vec3 defuse_light;
    //float ammount_diffuse = max(dot(o_normal, lightDir), 0.0f);
    //defuse_light = ammount_diffuse * Kd.xyz * c_lightColor;
    //
    //vec3 reflectDir = reflect(-lightDir, o_normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), Ks.w + 0.000001);
    //vec3 specular = Ks.xyz * spec;
    //
    //PixelLight = clamp(ambientLight + defuse_light, 0.0, 1.0) + specular;
    //
    //
    //finalPixel = vec4(PixelLight * color.xyz, color.a);
}