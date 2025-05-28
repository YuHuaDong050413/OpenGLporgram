#pragma once
#include <vector>
#include "Model.h"

class Cube : public Model
{
private:
	float m_Size;
public:
	Cube(const float size, const glm::mat4* modelMatrix);
	void AddTextureNormal(const std::vector<std::vector<float>>* position);
	void TransformPosition(const glm::mat4* modelMatrix, std::vector<float>& vertices);

};