#include "ImportModel.h"
#include <iostream>

ImportModel::ImportModel(const std::string& filename, const glm::mat4* modelMatrix)
{
	glm::vec3 vector3;
	glm::vec2 vector2;
	std::fstream stream(filename);
	std::string line = " ";
	while (!stream.eof())
	{
		std::getline(stream, line);
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream iss(line.substr(2));
			iss >> vector3.x >> vector3.y >> vector3.z;
			m_Positions.push_back(vector3);
		}

		if (line.substr(0, 2) == "vt")
		{
			std::istringstream iss(line.substr(2));
			iss >> vector2.x >> vector2.y;
			m_TexCoords.push_back(vector2);
		}

		if (line.substr(0, 2) == "vn")
		{
			std::istringstream iss(line.substr(2));
			iss >> vector3.x >> vector3.y >> vector3.z;
			m_Normals.push_back(vector3);
		}

		if (line.substr(0, 2) == "f ")
		{
			std::istringstream iss(line.substr(2));
			glm::vec3 indice;
			std::string v, t, n;
			for (int i = 0; i < 3; i++)
			{

				getline(iss, v, '/');
				getline(iss, t, '/');
				getline(iss, n, ' ');
				indice = glm::vec3(stoi(v) - 1, stoi(t) - 1, stoi(n) - 1);
				Indices.push_back(indice);
				
			}
		}

	}

	std::cout << Indices.size() << std::endl;
	for (std::vector<glm::vec3>::iterator it = Indices.begin(); it != Indices.end(); it++)
	{
		//进行transform的重构 让坐标*M矩阵
		TransformPosition(modelMatrix, it);

		//position
		m_Vertices.push_back(m_Positions[(*it).x].x);
		m_Vertices.push_back(m_Positions[(*it).x].y);
		m_Vertices.push_back(m_Positions[(*it).x].z);
		//texcoord
		m_Vertices.push_back(m_TexCoords[(*it).y].x);
		m_Vertices.push_back(m_TexCoords[(*it).y].y);
		//normal
		m_Vertices.push_back(m_Normals[(*it).z].x);
		m_Vertices.push_back(m_Normals[(*it).z].y);
		m_Vertices.push_back(m_Normals[(*it).z].z);

		m_Indices.push_back((unsigned int)(it - Indices.begin()));
	}
}

void ImportModel::TransformPosition(const glm::mat4* modelMatrix, const std::vector<glm::vec3>::iterator& it)
{
	glm::vec4 position = glm::vec4(m_Positions[(*it).x], 1.0f);
	glm::vec4 transformedPosition = (*modelMatrix) * position;
	m_Positions[(*it).x] = glm::vec3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
}