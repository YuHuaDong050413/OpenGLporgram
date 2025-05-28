#include "Torus.h"
#include <iostream>

Torus::Torus(const unsigned int prec, const float inner, const float outer, const glm::mat4* modelMatrix) : m_Prec(prec), m_Inner(inner), m_Outer(outer)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tTangents;
	std::vector<glm::vec3> sTangents;
	//第一个环
	for (unsigned int i = 0; i < m_Prec + 1; i++)
	{
		float amt = roRadians(i * 360.0f / m_Prec);
		glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 initPos(rMat * glm::vec4(0.5f, 0.0f, 0.0f, 1.0f) + glm::vec4(m_Inner, 0.0f, 0.0f, 1.0f));
		positions.push_back(initPos);

		glm::vec2 Texpos(0.0f, ((float)i / (float)m_Prec));
		texCoords.push_back(Texpos);

		tTangents.push_back(glm::vec3(rMat * glm::vec4(0.0f, -1.0f, 0.0f, 0.0f)));
		sTangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

		normals.push_back(glm::cross(tTangents[i], sTangents[i]));
	}


	//其他环
	for (unsigned int ring = 1; ring < m_Prec + 1; ring++)
	{
		for (int vert = 0; vert < m_Prec + 1; vert++)
		{
			float amt = roRadians(ring * 360.0f / m_Prec);
			glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), amt, glm::vec3(0.0f, 1.0f, 0.0f));
			positions.push_back(glm::vec3(rMat * glm::vec4(positions[vert], 1.0f)));

			glm::vec2 Texpos((float)ring / (float)m_Prec, texCoords[vert].y);  //ring*2/prec
			texCoords.push_back(Texpos);

			sTangents.push_back(glm::vec3(rMat * glm::vec4(sTangents[vert], 1.0f)));
			tTangents.push_back(glm::vec3(rMat * glm::vec4(tTangents[vert], 1.0f)));
			normals.push_back(glm::vec3(rMat * glm::vec4(normals[vert], 1.0f)));
		}
	}

	for (unsigned int i = 0;i < positions.size();i++)
	{
		//将每个顶点的位置变换到模型矩阵的位置
		TransformPosition(modelMatrix, i, positions);

		m_Vertices.push_back(positions[i].x);
		m_Vertices.push_back(positions[i].y);
		m_Vertices.push_back(positions[i].z);

		m_Vertices.push_back(texCoords[i].x);
		m_Vertices.push_back(texCoords[i].y);

		m_Vertices.push_back(normals[i].x);
		m_Vertices.push_back(normals[i].y);
		m_Vertices.push_back(normals[i].z);
		
	}

	for (unsigned int ring = 0; ring < m_Prec; ring++)
	{
		for (unsigned int vert = 0; vert < m_Prec; vert++)
		{
			m_Indices.push_back(ring * (m_Prec + 1) + vert);
			m_Indices.push_back((ring + 1) * (m_Prec + 1) + vert);
			m_Indices.push_back(ring * (m_Prec + 1) + (vert + 1));
			m_Indices.push_back(ring * (m_Prec + 1) + (vert + 1));
			m_Indices.push_back((ring + 1) * (m_Prec + 1) + vert);
			m_Indices.push_back((ring + 1) * (m_Prec + 1) + (vert + 1));
		}
	}

}

void Torus::TransformPosition(const glm::mat4* modelMatrix, const unsigned int& index, std::vector<glm::vec3>& positions)
{
	glm::vec4 position = glm::vec4(positions[index], 1.0f);
	glm::vec4 transformedPosition = (*modelMatrix) * position;
	positions[index] = glm::vec3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
}