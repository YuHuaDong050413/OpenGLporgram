#pragma once
#include <iostream>
#include <vector>
#include "Model.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class BatchRenderingModels
{
private:
	std::vector<Model*>* m_Models;
	int m_StartOffset;
	std::vector<float>* m_AllModelsVertices;
	std::vector<unsigned int>* m_AllModelsIndices;

private:
	void IntegrateVertices(const std::vector<Model*>* models);
	void IntegrateIndices(const std::vector<Model*>* models);

public:
	BatchRenderingModels();
	~BatchRenderingModels();

	void AddModel(Model* model);
	void IntegrateData();

	inline float* const getAllModelsVertices() { return &m_AllModelsVertices->at(0); }
	inline unsigned int* const getAllModelsIndices() { return &m_AllModelsIndices->at(0); } 

	inline unsigned int getAllModelsVerticesCount() { return m_AllModelsVertices->size(); }
	inline unsigned int getAllModelsIndicesCount() { return m_AllModelsIndices->size(); }

};

