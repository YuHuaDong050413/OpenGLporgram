#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtx/string_cast.hpp>
#include "glm\gtx\dual_quaternion.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "Shader.h"

class ShadowTexture
{
private:
	unsigned int m_FrameBufferID;
	unsigned int m_ShadowTextureID;

	glm::mat4 m_BMatrix;
	//VPæÿ’Û
	glm::mat4 m_LightVMatrix;
	glm::mat4 m_LightPMatrix;
public:
	ShadowTexture(GLFWwindow* window);
	void Init(float* currentLightPos, glm::mat4 currentPMatrix);
	void ShowShadowTexture(unsigned int slot) const;
	void SetShadowMVP(glm::mat4 mMat, Shader* shader);
	~ShadowTexture();

	inline glm::mat4 getLightVMat() const { return m_LightVMatrix; }
	inline glm::mat4 getLightPMat() const { return m_LightPMatrix; }
	inline glm::mat4 getBMat() const { return m_BMatrix; }

private:
	WindowSize getWindowSize(GLFWwindow* window) const;
	glm::mat4 setBMatrix() const;
	//≥ı ºªØ
	void setLightVMatrix(const float* currentLightPos);
	void setLightPMatrix(glm::mat4 currentPMatrix);
	
};

