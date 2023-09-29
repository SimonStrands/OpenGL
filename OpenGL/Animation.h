#pragma once
#include <glm.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

struct KeyFrame{
	std::vector<float> positionTimestamps;
	std::vector<float> rotationTimestamps;
	std::vector<float> scaleTimestamps;

	std::vector<glm::vec3> positions = {};
	std::vector<glm::vec4> rotations = {};
	std::vector<glm::vec3> scales = {};
};

class Animation {
public:
	float length = 0;
	float tick = 1.0f;
	std::map<std::string, KeyFrame> keyFrames;
};

struct Bone {
	std::string name;
	int parentIndex = -1;
	

	glm::mat4 inverseBindPoseMatrix;
	glm::mat4 boneMatrix;
	glm::mat4 boneMatrix;
	
};
