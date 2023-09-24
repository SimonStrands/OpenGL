#pragma once

#include <glm.hpp>

enum MaterialFlags{
	NONE = 0, 
	Albedo = 1,
	AmbientOcclusion = 2,
	HeightMap = 4, 
	NormalMap = 8
};

struct Material{
	unsigned int Albedo; 
	unsigned int AmbientOcclusion; 
	unsigned int HeightMap; 
	unsigned int NormalMap; 
	float Ns;
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	glm::vec3 Ke;
	float Ni;
	float d;
	MaterialFlags materialFlags;
	Material(){
		Albedo = 0;
		AmbientOcclusion = 0;
		HeightMap = 0;
		NormalMap = 0;
		materialFlags = MaterialFlags::NONE;
		Ns = 100.0f; 
		Ka = glm::vec3(0.5f,0.5f,0.5f);
		Kd = glm::vec3(0.5f,0.5f,0.5f);
		Ks = glm::vec3(0.5f,0.5f,0.5f);
		Ke = glm::vec3(0.5f,0.5f,0.5f);
		Ni = 1.0f;
		d = 1.0f;
	}
};
