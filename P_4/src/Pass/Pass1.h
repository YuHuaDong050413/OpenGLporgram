#pragma once
#include <iostream>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Renderer.h"

void PassOne(Shader* shader, BatchRenderingModels* batchrenderingmodels, MVStruct* MVStruct, ShadowTexture* shadowTexture, Renderer* renderer)
{
    shader->Bind();
    //Renderer renderer;
    //设置MVP矩阵
    {
        MVMatrix MVmatrix(MVStruct);
        glm::mat4 ShadowMVP = MVmatrix.getMMat() * shadowTexture->getLightVMat() * shadowTexture->getLightPMat();
            
        shader->Bind();
        shader->SetUniformMat4f("mvp_shadow", ShadowMVP);
        shader->Unbind();
    }
    //设置模型 顶点position
    {
        VertexArray va;
        VertexBuffer vb(batchrenderingmodels->getAllModelsVertices(),
            batchrenderingmodels->getAllModelsVerticesCount());

        VertexBufferLayout layout;
        //这是每个顶点的数据结构构成
        layout.Push<float>(3);  //position
        layout.Push<float>(2);  //texture
        layout.Push<float>(3);  //normal

        va.AddBufferOnlyPosition(vb, layout);
        //va.AddBuffer(vb, layout);
        IndexBuffer ib(batchrenderingmodels->getAllModelsIndices(),
            batchrenderingmodels->getAllModelsIndicesCount());

        va.Unbind();
        vb.Unbind();
        ib.Unbind();

        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
        GLCall(glEnable(GL_CULL_FACE));
        GLCall(glEnable(GL_DEPTH_TEST))
        GLCall(glDepthFunc(GL_LEQUAL));

        renderer->Draw(va, ib, *shader);
    }

}
