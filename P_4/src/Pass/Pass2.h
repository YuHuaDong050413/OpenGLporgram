#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Lights.h"
#include "Renderer.h"
#include "Matrix.h"
#include "Material.h"
#include "BatchRenderingModels.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "ShadowTexture.h"

void PassTwo(Shader* shader, GLFWwindow* window, 
    MaterialStruct* materialstruct, PositionalLightStruct* positionalLightStruct,
    BatchRenderingModels* batchrendering, MVStruct* MVStruct, ShadowTexture* shadowTexture, Renderer* renderer)
{
    //Renderer renderer;
    glm::mat4 VMat;
    {
        //P���� 
        PMatrix PMatrix(shader, window);
        //MV����
        MVMatrix MVmatrix(shader, MVStruct);
        VMat = MVmatrix.getVMat();
        //std::cout << "MMat:" << glm::to_string(MVmatrix.getMMat()) << std::endl;
        //shadowMVP����
        shadowTexture->SetShadowMVP(MVmatrix.getMMat(), shader);

    }

    //���� �ɵ���
    {
        Material Gold(materialstruct, shader);
    }

    {
        //ȫ�ֹ���
        GlobalLight globalLight(positionalLightStruct->m_GlobalAmbient, shader);
        Light pointLight(positionalLightStruct, shader, VMat);

    }

    VertexArray va;
    VertexBuffer vb(batchrendering->getAllModelsVertices(),
        batchrendering->getAllModelsVerticesCount());

    VertexBufferLayout layout;
    //����ÿ����������ݽṹ����
    layout.Push<float>(3);  //position
    layout.Push<float>(2);  //texture
    layout.Push<float>(3);  //normal

    va.AddBuffer(vb, layout);
    IndexBuffer ib(batchrendering->getAllModelsIndices(),
        batchrendering->getAllModelsIndicesCount());

    va.Unbind();
    vb.Unbind();
    ib.Unbind();

    GLCall(glClear(GL_DEPTH_BUFFER_BIT));
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glEnable(GL_DEPTH_TEST))
    GLCall(glDepthFunc(GL_LEQUAL));

    renderer->Draw(va, ib, *shader);
}