#include "Cube.h"
#include <iostream>
//有问题 暂时不用
Cube::Cube(const float size, const glm::mat4* modelMatrix) :m_Size(size)
{
	/*m_Vertices = 
	{
		-m_Size/2, -m_Size/2, -m_Size/2, 
		 m_Size/2, -m_Size/2, -m_Size/2,
		 m_Size/2, -m_Size/2,  m_Size/2,
		-m_Size/2, -m_Size/2,  m_Size/2,

		-m_Size/2,  m_Size/2, -m_Size/2,
		 m_Size/2,  m_Size/2, -m_Size/2,
		 m_Size/2,  m_Size/2,  m_Size/2,
		-m_Size/2,  m_Size/2,  m_Size/2
	};*/

	std::vector<float> position0 = { -m_Size / 2, -m_Size / 2, -m_Size / 2, };
	std::vector<float> position1 = { m_Size / 2, -m_Size / 2, -m_Size / 2, };
	std::vector<float> position2 = { m_Size / 2, -m_Size / 2, m_Size / 2, };
	std::vector<float> position3 = { -m_Size / 2, -m_Size / 2, m_Size / 2, }; 

	std::vector<float> position4 = { -m_Size / 2, m_Size / 2, -m_Size / 2, };
	std::vector<float> position5 = { m_Size / 2, m_Size / 2, -m_Size / 2, };
	std::vector<float> position6 = { m_Size / 2, m_Size / 2, m_Size / 2, };
	std::vector<float> position7 = { -m_Size / 2, m_Size / 2, m_Size / 2, }; 

	std::vector<std::vector<float>> position = { position0, position1, position2, position3, position4, position5, position6, position7 };
	AddTextureNormal(&position);

	//TransformPosition(modelMatrix, m_Vertices);

	m_Indices = {
		0, 2, 1,
		0, 3, 2,
		4, 5, 6,
		6, 7, 4,
		0, 1, 5,
		5, 4, 0,
		2, 3, 7,
		7, 6, 2,
		1, 2, 6,
		6, 5, 1,
		3, 0, 4,
		4, 7, 3,
	};
}


void Cube::AddTextureNormal(const std::vector<std::vector<float>>* position)
{
	//0
	m_Vertices.push_back(position->at(0)[0]);
	m_Vertices.push_back(position->at(0)[1]);
	m_Vertices.push_back(position->at(0)[2]);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0);
	//2
	m_Vertices.push_back(position->at(2)[0]);
	m_Vertices.push_back(position->at(2)[1]);
	m_Vertices.push_back(position->at(2)[2]);
	m_Vertices.push_back(0.75f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0);
	//1
	m_Vertices.push_back(position->at(1)[0]);
	m_Vertices.push_back(position->at(1)[1]);
	m_Vertices.push_back(position->at(1)[2]);
	m_Vertices.push_back(0.75f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0);
	//0
	m_Vertices.push_back(position->at(0)[0]);
	m_Vertices.push_back(position->at(0)[1]);
	m_Vertices.push_back(position->at(0)[2]);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0);
	//3
	m_Vertices.push_back(position->at(3)[0]);
	m_Vertices.push_back(position->at(3)[1]);
	m_Vertices.push_back(position->at(3)[2]);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0);
	//2
	m_Vertices.push_back(position->at(2)[0]);
	m_Vertices.push_back(position->at(2)[1]);
	m_Vertices.push_back(position->at(2)[2]);
	m_Vertices.push_back(0.75f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0);
	//4
	m_Vertices.push_back(position->at(4)[0]);
	m_Vertices.push_back(position->at(4)[1]);
	m_Vertices.push_back(position->at(4)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0);
	//5
	m_Vertices.push_back(position->at(5)[0]);
	m_Vertices.push_back(position->at(5)[1]);
	m_Vertices.push_back(position->at(5)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0);
	//6
	m_Vertices.push_back(position->at(6)[0]);
	m_Vertices.push_back(position->at(6)[1]);
	m_Vertices.push_back(position->at(6)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0);
	//6
	m_Vertices.push_back(position->at(6)[0]);
	m_Vertices.push_back(position->at(6)[1]);
	m_Vertices.push_back(position->at(6)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0);
	//7
	m_Vertices.push_back(position->at(7)[0]);
	m_Vertices.push_back(position->at(7)[1]);
	m_Vertices.push_back(position->at(7)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0);
	//4
	m_Vertices.push_back(position->at(4)[0]);
	m_Vertices.push_back(position->at(4)[1]);
	m_Vertices.push_back(position->at(4)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0);
	//0
	m_Vertices.push_back(position->at(0)[0]);
	m_Vertices.push_back(position->at(0)[1]);
	m_Vertices.push_back(position->at(0)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);			
	//1
	m_Vertices.push_back(position->at(1)[0]);
	m_Vertices.push_back(position->at(1)[1]);
	m_Vertices.push_back(position->at(1)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	//5
	m_Vertices.push_back(position->at(5)[0]);
	m_Vertices.push_back(position->at(5)[1]);
	m_Vertices.push_back(position->at(5)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	//5
	m_Vertices.push_back(position->at(5)[0]);
	m_Vertices.push_back(position->at(5)[1]);
	m_Vertices.push_back(position->at(5)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	//4
	m_Vertices.push_back(position->at(4)[0]);
	m_Vertices.push_back(position->at(4)[1]);
	m_Vertices.push_back(position->at(4)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	//0
	m_Vertices.push_back(position->at(0)[0]);
	m_Vertices.push_back(position->at(0)[1]);
	m_Vertices.push_back(position->at(0)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(-1.0f);
	//2
	m_Vertices.push_back(position->at(2)[0]);
	m_Vertices.push_back(position->at(2)[1]);
	m_Vertices.push_back(position->at(2)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	//3
	m_Vertices.push_back(position->at(3)[0]);
	m_Vertices.push_back(position->at(3)[1]);
	m_Vertices.push_back(position->at(3)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	//7
	m_Vertices.push_back(position->at(7)[0]);
	m_Vertices.push_back(position->at(7)[1]);
	m_Vertices.push_back(position->at(7)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	//7
	m_Vertices.push_back(position->at(7)[0]);
	m_Vertices.push_back(position->at(7)[1]);
	m_Vertices.push_back(position->at(7)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	//6
	m_Vertices.push_back(position->at(6)[0]);
	m_Vertices.push_back(position->at(6)[1]);
	m_Vertices.push_back(position->at(6)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	//2
	m_Vertices.push_back(position->at(2)[0]);
	m_Vertices.push_back(position->at(2)[1]);
	m_Vertices.push_back(position->at(2)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(1.0f);
	//1
	m_Vertices.push_back(position->at(1)[0]);
	m_Vertices.push_back(position->at(1)[1]);
	m_Vertices.push_back(position->at(1)[2]);
	m_Vertices.push_back(0.75f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//2
	m_Vertices.push_back(position->at(2)[0]);
	m_Vertices.push_back(position->at(2)[1]);
	m_Vertices.push_back(position->at(2)[2]);
	m_Vertices.push_back(0.75f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//6
	m_Vertices.push_back(position->at(6)[0]);
	m_Vertices.push_back(position->at(6)[1]);
	m_Vertices.push_back(position->at(6)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//6
	m_Vertices.push_back(position->at(6)[0]);
	m_Vertices.push_back(position->at(6)[1]);
	m_Vertices.push_back(position->at(6)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//5
	m_Vertices.push_back(position->at(5)[0]);
	m_Vertices.push_back(position->at(5)[1]);
	m_Vertices.push_back(position->at(5)[2]);
	m_Vertices.push_back(0.5f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//1
	m_Vertices.push_back(position->at(1)[0]);
	m_Vertices.push_back(position->at(1)[1]);
	m_Vertices.push_back(position->at(1)[2]);
	m_Vertices.push_back(0.75f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//3
	m_Vertices.push_back(position->at(3)[0]);
	m_Vertices.push_back(position->at(3)[1]);
	m_Vertices.push_back(position->at(3)[2]);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//0
	m_Vertices.push_back(position->at(0)[0]);
	m_Vertices.push_back(position->at(0)[1]);
	m_Vertices.push_back(position->at(0)[2]);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//4
	m_Vertices.push_back(position->at(4)[0]);
	m_Vertices.push_back(position->at(4)[1]);
	m_Vertices.push_back(position->at(4)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0);
	//4
	m_Vertices.push_back(position->at(4)[0]);
	m_Vertices.push_back(position->at(4)[1]);
	m_Vertices.push_back(position->at(4)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.33f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//7
	m_Vertices.push_back(position->at(7)[0]);
	m_Vertices.push_back(position->at(7)[1]);
	m_Vertices.push_back(position->at(7)[2]);
	m_Vertices.push_back(0.25f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	//3
	m_Vertices.push_back(position->at(3)[0]);
	m_Vertices.push_back(position->at(3)[1]);
	m_Vertices.push_back(position->at(3)[2]);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.66f);
	m_Vertices.push_back(-1.0f);
	m_Vertices.push_back(0.0f);
	m_Vertices.push_back(0.0f);
	
	

}

void Cube::TransformPosition(const glm::mat4* modelMatrix, std::vector<float>& vertices)
{
	for (int i = 0; i < vertices.size(); i += 3)
	{
		glm::vec4 position = glm::vec4(vertices[i], vertices[i + 1], vertices[i + 2], 1.0f);		
		glm::vec4 transformedPosition = (*modelMatrix) * position;
		vertices[i] = transformedPosition.x;
		vertices[i + 1] = transformedPosition.y;
		vertices[i + 2] = transformedPosition.z;
	}

}