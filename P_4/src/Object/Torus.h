#pragma once
#include <vector>
#include "Model.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Torus : public Model
{
private:
    unsigned int m_Prec;
    float m_Inner, m_Outer;
public:
    Torus(const unsigned int prec, const float inner, const float outer, const glm::mat4* modelMatrix);

private:
    void TransformPosition(const glm::mat4* modelMatrix, const unsigned int& index, std::vector<glm::vec3>& positions);
    float roRadians(float degree) { return degree * 3.14159 / 180.0f; }
};