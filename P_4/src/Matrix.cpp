#include "Matrix.h"
#include "Renderer.h"
//ģ�ͺ���ͼ����
#pragma region MV����

MVMatrix::MVMatrix(MVStruct* mvstruct) : MVMatrix(nullptr, mvstruct) {}

MVMatrix::MVMatrix(Shader* shader, MVStruct* mvstruct)

{
    {
        //position
        vMat_position = glm::translate(glm::mat4(1.0f), -(*mvstruct->camerapos));
        //rotation
        {
            glm::mat4 vrMat_x = glm::rotate(glm::mat4(1.0), glm::radians((*mvstruct->camerarot).x), glm::vec3(1.0, 0.0, 0.0));
            glm::mat4 vrMat_y = glm::rotate(glm::mat4(1.0), glm::radians((*mvstruct->camerarot).y), glm::vec3(0.0, 1.0, 0.0));
            glm::mat4 vrMat_z = glm::rotate(glm::mat4(1.0), glm::radians((*mvstruct->camerarot).z), glm::vec3(0.0, 0.0, 1.0));
            vMat_rotation = vrMat_x * vrMat_y * vrMat_z;
        }

    }

    {
        //position
        mMat_position = glm::translate(glm::mat4(1.0f), *mvstruct->modelpos);
        //rotation
        {
            glm::mat4 MRMatrix_X = glm::rotate(glm::mat4(1.0f), glm::radians((*mvstruct->modelrot).x), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 MRMatrix_Y = glm::rotate(glm::mat4(1.0f), glm::radians((*mvstruct->modelrot).y), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 MRMatrix_Z = glm::rotate(glm::mat4(1.0f), glm::radians((*mvstruct->modelrot).z), glm::vec3(0.0f, 0.0f, 1.0f));
            mMat_rotation = MRMatrix_X * MRMatrix_Y * MRMatrix_Z;
        }
        //scale
        mMat_scale = glm::scale(glm::mat4(1.0f), *mvstruct->modelscale);

    }


    if (shader)
    {
        mvMat = vMat_position * vMat_rotation * mMat_position * mMat_rotation * mMat_scale;
        //����ģ����ͼ����
        SetMVUnifrom(shader);
        SetInverseTransposeMVUniform(shader);

    }
    else
    {
        mvMat = glm::mat4(1.0f);
        return;
    }

}



void MVMatrix::SetMVUnifrom(Shader* shader)
{
    shader->Bind();
    shader->SetUniformMat4f("matrix.mv", mvMat);
    shader->Unbind();
}

void MVMatrix::SetInverseTransposeMVUniform(Shader* shader)
{
    shader->Bind();
    shader->SetUniformMat4f("matrix.normal", glm::transpose(glm::inverse(mvMat)));
    shader->Unbind();
}

#pragma endregion

#pragma region ͸�Ӿ���
//ͶӰ����  ͸�Ӿ���
PMatrix::PMatrix(GLFWwindow* window):PMatrix(nullptr, window) {}
PMatrix::PMatrix(Shader* shader, GLFWwindow* window)
{
    GLCall(glfwGetFramebufferSize(window, &m_Width, &m_Height));
    float aspectRatio = (float)m_Width / (float)m_Height;
    m_ProjMat = glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f);
    //����ͶӰ����
    if (shader)
    {
        SetPUniform(shader); 

    }
}

void PMatrix::SetPUniform(Shader* shader)
{
    shader->Bind();
    shader->SetUniformMat4f("matrix.p", m_ProjMat);
    shader->Unbind();
}

#pragma endregion

