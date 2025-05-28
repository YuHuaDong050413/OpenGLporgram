#include "Sphere.h"
#include <iostream>


Sphere::Sphere(const unsigned int prec, const float radis, const glm::mat4* modelMatrix): m_Prec(prec),m_Radis(radis)
{


	for (unsigned int i = 0; i <= m_Prec; i++)
	{
		for (unsigned int j = 0; j <= m_Prec; j++)
		{
			float y_Pos =  (float)cos(toRadians(180.0f - i * 180.0f / m_Prec));
			float x_Pos = -(float)cos(toRadians(j * 360.0f / m_Prec)) * (float)abs(cos(asin(y_Pos)));
			float z_Pos =  (float)sin(toRadians(j * 360.0f / m_Prec)) * (float)abs(cos(asin(y_Pos)));
			
			float x_Tex = (float)j / (float)m_Prec;
			float y_Tex = (float)i / (float)m_Prec;

			float x_Nor = x_Pos;
			float y_Nor = y_Pos;
			float z_Nor = z_Pos;

			glm::vec3 position = m_Radis * glm::vec3(x_Pos, y_Pos, z_Pos); 

			TransformPosition(modelMatrix, position);

			m_Vertices.push_back(position.x);
			m_Vertices.push_back(position.y);
			m_Vertices.push_back(position.z);

			m_Vertices.push_back(x_Tex);
			m_Vertices.push_back(y_Tex);

			m_Vertices.push_back(x_Nor);
			m_Vertices.push_back(y_Nor);
			m_Vertices.push_back(z_Nor);
			
		}
	}

	for (unsigned int i = 0; i < m_Prec; i++)
	{
		for (unsigned int j = 0; j < m_Prec; j++)
		{
			m_Indices.push_back(i * (m_Prec + 1) + j);
			m_Indices.push_back(i * (m_Prec + 1) + j + 1); 
			m_Indices.push_back((i + 1)*(m_Prec + 1) + j); 
			m_Indices.push_back(i * (m_Prec + 1) + j + 1); 
			m_Indices.push_back((i + 1) * (m_Prec + 1) + j + 1);
			m_Indices.push_back((i + 1) * (m_Prec + 1) + j);
			
		}
	}

	
}

void Sphere::TransformPosition(const glm::mat4* modelMatrix, glm::vec3& position)
{
	glm::vec4 Position = glm::vec4(position, 1.0f);
	glm::vec4 transformedPosition = (*modelMatrix) * Position;
	position = glm::vec3(transformedPosition.x, transformedPosition.y, transformedPosition.z);
}
