#include "BatchRenderingModels.h"

BatchRenderingModels::BatchRenderingModels(): m_StartOffset(0)
{
	m_Models = new std::vector<Model*>;
	m_AllModelsIndices = new std::vector<unsigned int>;
	m_AllModelsVertices = new std::vector<float>;
}

void BatchRenderingModels::AddModel(Model* model)
{
	if (m_Models != nullptr)
	{
		m_Models->push_back(model);
	}
}

void BatchRenderingModels::IntegrateData()
{
	IntegrateIndices(m_Models);
	IntegrateVertices(m_Models); 
	
}

void BatchRenderingModels::IntegrateVertices(const std::vector<Model*>* models)
{
	if (models != nullptr)
	{
		for (int i = 0; i < models->size(); i++)
		{
			if (models->at(i) != nullptr)
			{
				std::vector<float> modelvertices = models->at(i)->getModelData().vertices;
				m_AllModelsVertices->insert(m_AllModelsVertices->end(), 
					modelvertices.begin(), modelvertices.end());

			}
			else
			{
				std::cout << "Model" << i << " is null" << std::endl;
				return;
			}
		}

	}
	else
	{
		std::cout << "No models found" << std::endl;
		return;
	}
}

void BatchRenderingModels::IntegrateIndices(const std::vector<Model*>* models)
{
	if (models != nullptr)
	{
		for (int i = 0; i < models->size(); i++)
		{
			if (models->at(i) != nullptr)
			{
				std::vector<unsigned int> modelindices = models->at(i)->getModelData().indices;
				for (int j = 0; j < modelindices.size(); j++)
				{
					modelindices[j] += m_StartOffset;
				}
				m_AllModelsIndices->insert(m_AllModelsIndices->end(), modelindices.begin(), modelindices.end());
				m_StartOffset += models->at(i)->getIndicesCount(); 

			}
			else
			{
				std::cout << "Model" << i << " is null" << std::endl;
				return;
			}
		}

	}
	else
	{
		std::cout << "No models found" << std::endl;
		return;
	}
}


BatchRenderingModels::~BatchRenderingModels()
{
	delete m_Models, m_AllModelsIndices, m_AllModelsVertices;
}