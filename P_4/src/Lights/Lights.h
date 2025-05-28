#pragma once
#include "Shader.h"
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum LightType
{
	DIRECTIONAL_LIGHT,
	POSITIONAL_LIGHT,
	SPOT_LIGHT,
	NONE
};



struct LightStruct
{
	float* m_GlobalAmbient;
	float* m_Ambient;
	float* m_Diffuse;
	float* m_Specular;
	LightType m_Type;

	LightStruct(float* globalambient = nullptr, float* ambient = nullptr, float* diffuse = nullptr, float* specular = nullptr, LightType type = NONE):
		m_GlobalAmbient(globalambient), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Type(type) {}

	virtual void DisplayLightInfo() const
	{
		std::cout << "Base Light" << std::endl;
	}

};

struct DirectionalLightStruct: public LightStruct
{
	float* m_Direction;
	DirectionalLightStruct(float* globalambient = nullptr, float* ambient = nullptr, float* diffuse = nullptr, float* specular = nullptr, float* direction = nullptr):
		LightStruct(globalambient, ambient, diffuse, specular, DIRECTIONAL_LIGHT), m_Direction(direction){}

	void DisplayLightInfo() const override
	{
		std::cout << "Directional Light" << std::endl;
	}
};

struct PositionalLightStruct: public LightStruct
{
	float* m_Position;
	PositionalLightStruct(float* globalambient = nullptr, float* ambient = nullptr, float* diffuse = nullptr, float* specular = nullptr, float* position = nullptr):
		LightStruct(globalambient, ambient, diffuse, specular, POSITIONAL_LIGHT), m_Position(position){}

	void DisplayLightInfo() const override
	{
		std::cout << "Positional Light" << std::endl;
	}
};

struct SpotLightStruct: public LightStruct
{
	float* m_Position;
	float* m_Direction;
	float* m_CutOff;
	float* m_Exponent;
	SpotLightStruct(float* globalambient = nullptr, float* ambient = nullptr, float* diffuse = nullptr, float* specular = nullptr, float* position = nullptr, float* direction = nullptr, float* cutOff = nullptr, float* exponent = nullptr):
		LightStruct(globalambient, ambient, diffuse, specular, SPOT_LIGHT), m_Position(position), m_Direction(direction), m_CutOff(cutOff), m_Exponent(exponent){}

	void DisplayLightInfo() const override
	{
		std::cout << "Spot Light" << std::endl;
	}

};




class Light
{
private:
	Shader* m_Shader;
public:
	Light(LightStruct* light, Shader* shader, glm::mat4 vMatrix = glm::mat4(1.0f));
	~Light();
};

class GlobalLight
{
private:
	Shader* m_Shader;
public:
	GlobalLight(float* globalLight, Shader* shader);
	~GlobalLight();
};