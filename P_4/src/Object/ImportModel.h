#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Model.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ImportModel : public Model
{
private:
	std::vector<glm::vec3> m_Positions;
	std::vector<glm::vec2> m_TexCoords;
	std::vector<glm::vec3> m_Normals;

	std::vector<glm::vec3> Indices;
private:
	void TransformPosition(const glm::mat4* modelMatrix, const std::vector<glm::vec3>::iterator& it);

public:
	ImportModel(const std::string& filePath, const glm::mat4* modelMatrix);

};