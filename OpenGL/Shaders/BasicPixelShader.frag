#version 330 core 
        
layout(location = 0) out vec4 color;
    
in vec4 CPosition;

void main(){ 
    color = vec4(CPosition.xyz, 1.0);
    //color = vec4(1.0, 1.0, 1.0, 1.0);
}