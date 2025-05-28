#include "Transform.h"

Transform::Transform():m_ModelMatrix(1.0f) {}

void Transform::setModelMatrix(const glm::vec3* position, const glm::vec3* rotation, const glm::vec3* scale)
{
	glm::mat4 modelPositionMatrix = glm::translate(glm::mat4(1.0f), *position);

	glm::mat4 modelRotationMatrix;
	{
		glm::mat4 MRMatrix_X = glm::rotate(glm::mat4(1.0f), glm::radians(rotation->x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 MRMatrix_Y = glm::rotate(glm::mat4(1.0f), glm::radians(rotation->y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 MRMatrix_Z = glm::rotate(glm::mat4(1.0f), glm::radians(rotation->z), glm::vec3(0.0f, 0.0f, 1.0f));
		modelRotationMatrix = MRMatrix_X * MRMatrix_Y * MRMatrix_Z;
	}

	glm::mat4 modelScaleMatrix = glm::scale(glm::mat4(1.0f), *scale);

	m_ModelMatrix = modelPositionMatrix * modelRotationMatrix * modelScaleMatrix;
}
