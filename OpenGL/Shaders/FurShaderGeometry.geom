#version 420 core

in vec4 o_fragPos[];
in vec2 o_uv[];
in vec3 o_normal[];

out vec4 i_fragPos;
out vec2 i_uv;
out vec3 i_normal;
out float i_lvl;

layout(triangles) in;
layout (triangle_strip, max_vertices = 144) out;
//layout (triangle_strip, max_vertices = 150) out;

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

    //const int nrOfLayers = 1;
    const int nrOfLayers = 48;
    const float layerdiff = 0.01;

void main()
{ 
    mat4 MVP = (view) * projection;
    for(int v = 0; v < nrOfLayers; ++v){
        for (int i = 0; i < gl_in.length(); ++i)
        {
            i_fragPos = (o_fragPos[i] + (vec4(o_normal[i], 0) * (v * layerdiff)));
            i_uv = o_uv[i];
            i_normal = o_normal[i];
            i_lvl = v;
            gl_Position = i_fragPos * MVP;
            EmitVertex();
        }
        EndPrimitive();
    }
}