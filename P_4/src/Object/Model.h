#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

struct ModelData
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
};


class Model
{
protected:

	std::vector<float> m_Vertices;
	std::vector<unsigned int> m_Indices;
	////Modelæÿ’Û
	//glm::mat4* m_ModelMatrix;

public:
	inline ModelData getModelData() const { return { m_Vertices, m_Indices }; }
	inline int getVerticesCount() const { return m_Vertices.size(); }
	inline int getIndicesCount() const { return m_Indices.size(); }
};

