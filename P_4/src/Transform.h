#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Transform
{
private:
	//������������ �ڳ�������ʱ���ı� �Ͳ�����whileѭ���е�����
	/*glm::vec3* m_ModelPosition;
	glm::vec3* m_ModelRotation;
	glm::vec3* m_ModelScale;*/
public:
	glm::mat4 m_ModelMatrix;
public:
	Transform();
	void setModelMatrix(const glm::vec3* position, const glm::vec3* rotation, const glm::vec3* scale);

};

