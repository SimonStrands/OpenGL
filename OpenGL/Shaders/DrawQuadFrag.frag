#version 420 core
        
layout(location = 0) out vec4 finalPixel;

in vec2 o_uv;

layout(binding = 0)uniform sampler2D ambientTexture;

void main(){ 
    finalPixel = texture(ambientTexture, o_uv);
}