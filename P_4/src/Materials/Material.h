#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

struct MaterialStruct
{
	MaterialStruct(float* ambient, float* diffuse, float* specular, float* shininess)
		: m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess) {}
	float* m_Ambient;
	float* m_Diffuse;
	float* m_Specular;
	float* m_Shininess;
};

class Material
{
private:
	Shader* m_Shader;
public:
	Material(MaterialStruct* materialStruct, Shader* shader) :m_Shader(shader)
	{
		m_Shader->Bind();
		m_Shader->SetUniform4f("material.ambient", materialStruct->m_Ambient[0], materialStruct->m_Ambient[1], materialStruct->m_Ambient[2], materialStruct->m_Ambient[3]);
		m_Shader->SetUniform4f("material.diffuse", materialStruct->m_Diffuse[0], materialStruct->m_Diffuse[1], materialStruct->m_Diffuse[2], materialStruct->m_Diffuse[3]);
		m_Shader->SetUniform4f("material.specular", materialStruct->m_Specular[0], materialStruct->m_Specular[1], materialStruct->m_Specular[2], materialStruct->m_Specular[3]);
		m_Shader->SetUniform1f("material.shininess", materialStruct->m_Shininess[0]);
	}
	~Material()
	{
		m_Shader->Unbind();
	}
};

//struct Gold : public Material
//{
//	glm::vec4 m_Ambient = glm::vec4(0.2473, 0.1995, 0.0745, 1.0);
//	glm::vec4 m_Diffuse = glm::vec4(0.7516, 0.6065, 0.2265, 1.0);
//	glm::vec4 m_specular = glm::vec4(0.6283, 0.5558, 0.3661, 1.0);
//	float m_Shininess = 51.2;
//};
//
//struct Silver : public Material
//{
//	glm::vec4 m_Ambient = glm::vec4(0.1923, 0.1923, 0.1923, 1.0);
//	glm::vec4 m_Diffuse = glm::vec4(0.5075, 0.5075, 0.5075, 1.0);
//	glm::vec4 m_specular = glm::vec4(0.5083, 0.5083, 0.5083, 1.0);
//	float m_Shininess = 51.2;
//};
//
//struct jade : public Material  //”Ò
//{
//	glm::vec4 m_Ambient = glm::vec4(0.1350, 0.2225, 0.1575, 0.95);
//	glm::vec4 m_Diffuse = glm::vec4(0.5400, 0.8900, 0.6300, 0.95);
//	glm::vec4 m_specular = glm::vec4(0.3162, 0.3162, 0.3162, 0.95);
//	float m_Shininess = 12.8;
//};
//
//struct Pearl : public Material //’‰÷È
//{
//	glm::vec4 m_Ambient = glm::vec4(0.25, 0.2073, 0.2073, 0.922);
//	glm::vec4 m_Diffuse = glm::vec4(1.0, 0.829, 0.829, 0.922);
//	glm::vec4 m_specular = glm::vec4(0.2966, 0.2966, 0.2966, 0.922);
//	float m_Shininess = 11.264;
//};