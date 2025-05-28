#include "ShadowTexture.h"
#include "Renderer.h"



ShadowTexture::ShadowTexture(GLFWwindow* window)
{
	m_BMatrix = setBMatrix();
	WindowSize windowSize = getWindowSize(window);
	//����֡������
	GLCall(glGenFramebuffers(1, &m_FrameBufferID));
	//�����������
	GLCall(glGenTextures(1, &m_ShadowTextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ShadowTextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
		windowSize.width, windowSize.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0));
	//�����������
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
}

ShadowTexture::~ShadowTexture()
{
	GLCall(glDeleteFramebuffers(1, &m_FrameBufferID));
	GLCall(glDeleteTextures(1, &m_ShadowTextureID));

}

void ShadowTexture::Init(float* currentLightPos, glm::mat4 currentPMatrix)
{
	setLightVMatrix(currentLightPos);
	setLightPMatrix(currentPMatrix);
	//��֡���������������
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID));
	GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_ShadowTextureID, 0));
	//�����ӿ�
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glEnable(GL_DEPTH_TEST));
}

void ShadowTexture::ShowShadowTexture(unsigned int slot) const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0)); //0����Ĭ��֡������
	GLCall(glActiveTexture(GL_TEXTURE1));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ShadowTextureID));
	GLCall(glDrawBuffer(GL_FRONT));
}

void ShadowTexture::SetShadowMVP(glm::mat4 mMat, Shader* shader)
{
	glm::mat4 shadowMVP2 = m_LightPMatrix * m_LightVMatrix * m_BMatrix * mMat;
	shader->Bind();
	shader->SetUniformMat4f("matrix.shadowMVP", shadowMVP2);
	shader->Unbind();
}



///<summary>
///˽�г�Ա����s
///</summary>
WindowSize ShadowTexture::getWindowSize(GLFWwindow* window) const
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	return WindowSize(width, height);
}

glm::mat4 ShadowTexture::setBMatrix() const
{
	return glm::mat4(
		0.5f, 0.0f, 0.0f, 0.5f,
		0.0f, 0.5f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f, 0.5f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

void ShadowTexture::setLightVMatrix(const float* currentLightPos)
{
	glm::vec3 lightPos = glm::vec3(currentLightPos[0], currentLightPos[1], currentLightPos[2]);
	m_LightVMatrix = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	///<param name="�ڶ�������"> �����Ŀ�����ԭ��(0,0,0) </param>
	///<param name="����������"> ������ӽ���Y�������� </param>
}

void ShadowTexture::setLightPMatrix(glm::mat4 currentPMatrix)
{
	m_LightPMatrix = currentPMatrix;
}
