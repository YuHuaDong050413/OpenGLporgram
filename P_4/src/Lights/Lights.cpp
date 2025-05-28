#include "Lights.h"
#include <iostream>
#include "Renderer.h"

Light::Light(LightStruct* light, Shader* shader, glm::mat4 vMatrix):m_Shader(shader)
{
	m_Shader->Bind();

	switch (light->m_Type)
	{
		default:
			ASSERT(false, "Invalid light type");
			break;
		case LightType::DIRECTIONAL_LIGHT:
		{
			DirectionalLightStruct* dirLight = (DirectionalLightStruct*)(light);
			m_Shader->SetUniform4f("directionaldirLight.ambient", dirLight->m_Ambient[0], dirLight->m_Ambient[1], dirLight->m_Ambient[2], dirLight->m_Ambient[3]);
			m_Shader->SetUniform4f("directionaldirLight.diffuse", dirLight->m_Diffuse[0], dirLight->m_Diffuse[1], dirLight->m_Diffuse[2], dirLight->m_Diffuse[3]);
			m_Shader->SetUniform4f("directionaldirLight.specular", dirLight->m_Specular[0], dirLight->m_Specular[1], dirLight->m_Specular[2], dirLight->m_Specular[3]);
			m_Shader->SetUniform3f("directionaldirLight.direction", dirLight->m_Direction[0], dirLight->m_Direction[1], dirLight->m_Direction[2]);
			break;

		}
		case LightType::POSITIONAL_LIGHT:
		{
			PositionalLightStruct* pointLight = (PositionalLightStruct*)(light);
			m_Shader->SetUniform4f("positionalLight.ambient", pointLight->m_Ambient[0], pointLight->m_Ambient[1], pointLight->m_Ambient[2], pointLight->m_Ambient[3]);
			m_Shader->SetUniform4f("positionalLight.diffuse", pointLight->m_Diffuse[0], pointLight->m_Diffuse[1], pointLight->m_Diffuse[2], pointLight->m_Diffuse[3]);
			m_Shader->SetUniform4f("positionalLight.specular", pointLight->m_Specular[0], pointLight->m_Specular[1], pointLight->m_Specular[2], pointLight->m_Specular[3]);

			glm::vec3 LightPosV = glm::vec3(vMatrix * glm::vec4(pointLight->m_Position[0], pointLight->m_Position[1], pointLight->m_Position[2], 1.0f));
			m_Shader->SetUniform3f("positionalLight.position", LightPosV.x, LightPosV.y, LightPosV.z);
			break;

		}
		case LightType::SPOT_LIGHT:
		{
			SpotLightStruct* spotLight = (SpotLightStruct*)(light);
			m_Shader->SetUniform4f("spotLight.ambient", spotLight->m_Ambient[0], spotLight->m_Ambient[1], spotLight->m_Ambient[2], spotLight->m_Ambient[3]);
			m_Shader->SetUniform4f("spotLight.diffuse", spotLight->m_Diffuse[0], spotLight->m_Diffuse[1], spotLight->m_Diffuse[2], spotLight->m_Diffuse[3]);
			m_Shader->SetUniform4f("spotLight.specular", spotLight->m_Specular[0], spotLight->m_Specular[1], spotLight->m_Specular[2], spotLight->m_Specular[3]);
			m_Shader->SetUniform3f("spotLight.position", spotLight->m_Position[0], spotLight->m_Position[1], spotLight->m_Position[2]);
			m_Shader->SetUniform3f("spotLight.direction", spotLight->m_Direction[0], spotLight->m_Direction[1], spotLight->m_Direction[2]);
			m_Shader->SetUniform1f("spotLight.cutOff", *spotLight->m_CutOff);
			m_Shader->SetUniform1f("spotLight.Exponent", *spotLight->m_Exponent);
			break;

		}
	}
	
}

Light::~Light()
{
	m_Shader->Unbind();
}


GlobalLight::GlobalLight(float* globalLight, Shader* shader) :m_Shader(shader)
{
	m_Shader->Bind();
	m_Shader->SetUniform4f("globalLight.ambient", globalLight[0], globalLight[1], globalLight[2], globalLight[3]);
}

GlobalLight::~GlobalLight()
{
	m_Shader->Unbind();
}

