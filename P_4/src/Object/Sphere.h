#pragma once
#include <vector>
#include "Model.h"
#include <cmath>

class Sphere : public Model
{
private:
	unsigned int m_Prec;
	float m_Radis;

public:
	Sphere(const unsigned int prec, const float radius, const glm::mat4* modelMatrix);
	
private:
	void TransformPosition(const glm::mat4* modelMatrix, glm::vec3& position);
	float toRadians(float degrees) { return degrees * 3.14159f / 180.0f; }
};