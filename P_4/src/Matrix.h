#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

struct MVStruct
{
    glm::vec3* camerapos;
    glm::vec3* camerarot;
    glm::vec3* modelpos;
    glm::vec3* modelrot;
    glm::vec3* modelscale;
    MVStruct(glm::vec3* camerapos, glm::vec3* camerarot, glm::vec3* modelpos, glm::vec3* modelrot, glm::vec3* modelscale)
        : camerapos(camerapos), camerarot(camerarot), modelpos(modelpos), modelrot(modelrot), modelscale(modelscale) {}
};


#pragma region MVæÿ’Û
class MVMatrix
{
private:
    glm::mat4 vMat_position, vMat_rotation, 
              mMat_position, mMat_rotation, mMat_scale,
              mvMat;
public:
    MVMatrix(Shader* shader,MVStruct* mvstruct);
    MVMatrix(MVStruct* mvstruct);

    inline glm::mat4 getMVMat() const { return mvMat; }
    inline glm::mat4 getMMat() const { return (mMat_position * mMat_rotation * mMat_scale); }
    inline glm::mat4 getVMat() const { return (vMat_position * vMat_rotation); }
    inline glm::mat4 getMVInvTrMat() const { return glm::transpose(glm::inverse(mvMat)); }

private:
    void SetMVUnifrom(Shader* shader);
    void SetInverseTransposeMVUniform(Shader* shader);

};
#pragma endregion








#pragma region Õ∏ ”æÿ’Û
class PMatrix
{
private:
    int m_Width, m_Height;
    glm::mat4 m_ProjMat;
public:
    PMatrix(GLFWwindow* window);
    PMatrix(Shader* shader, GLFWwindow* window);
    inline glm::mat4 getPMat() { return m_ProjMat; }
private:
    void SetPUniform(Shader* shader);

};

#pragma endregion
