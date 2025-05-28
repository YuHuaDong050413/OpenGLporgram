#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShadowTexture.h"
#include "Texture.h"
#include "Matrix.h"
#include "Move.h"
#include "GUI.h"

#include "BatchRenderingModels.h" //批量渲染模型
#include "Transform.h" //每个模型对应的transform

#include "Sphere.h"
#include "Cube.h"
#include "Torus.h"
#include "ImportModel.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include <ImGui/imgui_impl_opengl3.h>

#include "Lights.h"
#include "Material.h"

#include "Pass1.h" 
#include "Pass2.h"


static float moveSpeed = 0.02f;

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
    if (yoffset > 0)
    {
        if (moveSpeed < 0.195f)
            moveSpeed += 0.005f;
    }
    else
    {
        if (moveSpeed > 0.01f)
            moveSpeed -= 0.005f;
        
    }
}

void window_reshape_callback(GLFWwindow* window, int newwidth, int newheight)
{
    glViewport(0, 0, newwidth, newheight);
    glm::mat4 pMat = glm::perspective(glm::radians(60.0f), (float)newwidth / (float)newheight, 0.1f, 1000.0f);
}

int main()
{
#pragma region 初始化


    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    glewExperimental = true; // Needed for core profile
    glewInit();

    
    //TODO: make sure the version of glsl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1800, 1200, "P_4", NULL, NULL);  //4:3



    glfwMakeContextCurrent(window);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //回调函数
    glfwSetWindowSizeCallback(window, window_reshape_callback);
    glfwSetScrollCallback(window, scroll_callback);

    GUI GUI(window);
    std::cout << glGetString(GL_VERSION) << std::endl;

    //TODO: init
    
    if (glewInit() != GLEW_OK)
        std::cout << "error" << std::endl;
#pragma region 设置GL
    //启动深度测试
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); //如果当前像素的深度值小于Z-buffer中的值，渲染该像素。
    //启动背面剔除
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW); 
#pragma endregion

#pragma endregion
    
#pragma region 导入模型
    BatchRenderingModels BatchOne;
    {

        //模型一：
        Transform JetTransform;
        {
            glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
            JetTransform.setModelMatrix(&position, &rotation, &scale);
        }
        ImportModel importModel("res/Obj/Jet.txt", &JetTransform.m_ModelMatrix);
        BatchOne.AddModel(&importModel);

        ////模型二：
        Transform SphereTransform;
        {
            glm::vec3 position = glm::vec3(0.0, 0.0, -5.0);  
            glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
            SphereTransform.setModelMatrix(&position, &rotation, &scale);
        }
        Sphere sphere(6, 1, &SphereTransform.m_ModelMatrix);
        BatchOne.AddModel(&sphere);

        //模型三：
       /* Transform CubeTransform;
        {
            glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
            CubeTransform.setModelMatrix(&position, &rotation, &scale);
        }
        Cube cube(5, &CubeTransform.m_ModelMatrix);
        BatchRenderingModels.AddModel(&cube); */

        //模型四：
        /*Transform TorusTransform;
        {
            glm::vec3 position = glm::vec3(0.0, 10.0, 0.0);
            glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
            TorusTransform.setModelMatrix(&position, &rotation, &scale);
        }
        Torus torus(48, 1, 0.3, &TorusTransform.m_ModelMatrix);
        BatchOne.AddModel(&torus);*/

        /*Transform TorusTransform2;
        {
            glm::vec3 position = glm::vec3(0.0, 10.0, 0.0);
            glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);
            TorusTransform2.setModelMatrix(&position, &rotation, &scale);
        }
        Torus torus2(48, 5, 0.3, &TorusTransform2.m_ModelMatrix);
        BatchOne.AddModel(&torus2);*/


        BatchOne.IntegrateData();
    }

#pragma endregion
    //阴影纹理
    ShadowTexture ShadowTexture(window);
    //PassOne的shader
    Shader PassOneShader("res/shaders/PassOne.vert", "res/shaders/PassOne.frag"); //可以尝试一下去掉片段着色器

    //PassTwo的shader
    Shader PassTwoShader("res/shaders/PassTwo.vert", "res/shaders/PassTwo.frag");
    {
        PassTwoShader.Bind(); 
        //纹理贴图
        Texture texture("res/textures/Color.png"); 
        texture.Bind(); 
        PassTwoShader.SetUniform1i("u_Texture", 0); 
        //set uniform

        PassTwoShader.Unbind(); 

    }

    ///<summary>
    ///这是老项目的部分
    ///</summary>
    //VertexArray va;
    //VertexBuffer vb(BatchOne.getAllModelsVertices(),
    //    BatchOne.getAllModelsVerticesCount());

    //VertexBufferLayout layout;
    ////这是每个顶点的数据结构构成
    //layout.Push<float>(3);  //position
    //layout.Push<float>(2);  //texture
    //layout.Push<float>(3);  //normal

    //va.AddBuffer(vb, layout);
    //IndexBuffer ib(BatchOne.getAllModelsIndices(),
    //    BatchOne.getAllModelsIndicesCount());

    //va.Unbind();
    //vb.Unbind();
    //ib.Unbind();
    //
    //Shader shader("res/shaders/Vertex.vert", "res/shaders/Fragment.frag");
    //shader.Bind();
    //shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    ////纹理贴图
    //Texture texture("res/textures/Color.png");
    //texture.Bind();
    //shader.SetUniform1i("u_Texture", 0);
    ////set uniform
    //    
    //shader.Unbind();
        

#pragma region 所有基础数据
    //视角和模型MV
    glm::vec3 camera_Pos = glm::vec3(0.0, 0.0, -3.5);
    glm::vec3 Camera_rot = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 Model_pos = glm::vec3(0.0, 0.0, 0.0); //0.0, -1.0, 0.0
    glm::vec3 Model_rot = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 Model_scl = glm::vec3(1.0, 1.0, 1.0);
    MVStruct MVStruct(&camera_Pos, &Camera_rot, &Model_pos, &Model_rot, &Model_scl);
    //相机移动

    //灯光 可调节
    float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float positionalAmbient[4] = {0.0, 0.0, 0.0, 1.0};
    float positionalDiffuse[4] = {1.0, 1.0, 1.0, 1.0};
    float positionalSpecular[4] = {1.0, 1.0, 1.0, 1.0};
    float positionalPosition[3] = {5.0, 2.0, 2.0};
    //位置光
    PositionalLightStruct positionalLightStruct(globalAmbient,
        positionalAmbient, positionalDiffuse, positionalSpecular, positionalPosition);

    //材质 可调节
    float ambient[4] = { 0.24725, 0.1995, 0.0745, 1.0 };
    float diffuse[4] = { 0.75164, 0.60648, 0.22648, 1.0 };
    float specular[4] = { 0.628281, 0.555802, 0.366065, 1.0 };
    float shininess = 51.2;
    MaterialStruct GoldStruct(ambient, diffuse, specular, &shininess);

#pragma endregion

    
    Renderer renderer;

        
    while (!glfwWindowShouldClose(window))
    {
        //TODO: render here display
        renderer.ClearColor({ 0.5f, 0.5f, 0.5f, 1.0f });
        renderer.ClearDepth();

        GUI.UI_NewFrame();

        Move move(0.02, &moveSpeed, MVStruct.camerapos);

#pragma region 设置uniform
        //glm::mat4 VMat;
        //{
        //    //P矩阵 
        //    PMatrix PMatrix(&shader, window);
        //    //MV矩阵
        //    MVMatrix MVmatrix(&shader, &MVStruct);
        //    VMat = MVmatrix.getVMat();

        //}

        ////材质 可调节
        //{
        //    Material Gold(&GoldStruct, &shader); 
        //}

        //{
        //    //全局光照
        //    GlobalLight globalLight(positionalLightStruct.m_GlobalAmbient, &shader);
        //    Light pointLight(&positionalLightStruct, &shader, VMat);

        //}
#pragma region 绘制模型
        //renderer.Draw(va, ib, shader);
#pragma endregion
        

#pragma endregion
        //这里有问题
        PMatrix PMatrix(window);
        ShadowTexture.Init(positionalPosition, PMatrix.getPMat());
        //PassOne
        PassOne(&PassOneShader, &BatchOne, &MVStruct, &ShadowTexture, &renderer);
        //显示阴影纹理
        ShadowTexture.ShowShadowTexture(1);
        //PassTwo
        PassTwo(&PassTwoShader, window, &GoldStruct, &positionalLightStruct, &BatchOne, &MVStruct, &ShadowTexture, &renderer);



        {
            WindowSize windowSize = GUI.getWindowSize();
            ImGui::SetNextWindowPos(ImVec2(windowSize.width - 450, 0));
            ImGui::SetNextWindowSizeConstraints(ImVec2(450, windowSize.height), ImVec2(450, windowSize.height));
            ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove);
            

            ImGui::BeginChild("Camera & Model", ImVec2(400, 200));
            ImGui::Text("CAMERA & MODEL");
            ImGui::Text("Camera");
            ImGui::SliderFloat3("C_Position", &MVStruct.camerapos->x, -180.0f, 180.0f);
            ImGui::SliderFloat3("C_Rotation", &MVStruct.camerarot->x, -360.0f, 360.0f);
            ImGui::SliderFloat("Speed",       &moveSpeed,      0.01f,   0.2f);
            ImGui::Text("Model");
            ImGui::SliderFloat3("M_Position", &MVStruct.modelpos->x,  -10.0f,  10.0f);
            ImGui::SliderFloat3("m_Rotation", &MVStruct.modelrot->x, -360.0f, 360.0f);
            ImGui::SliderFloat3("M_Scale",    &MVStruct.modelscale->x,    0.1f,   5.0f);
            ImGui::EndChild();

            ImGui::BeginChild("Light", ImVec2(400, 200));
            ImGui::Text("GLOBAL LIGHT");
            ImGui::SliderFloat4("Light Color", positionalLightStruct.m_GlobalAmbient, 0.0f, 1.0f);

            ImGui::Text("MATERIAL");
            ImGui::SliderFloat4("Ambient", GoldStruct.m_Ambient, 0.0f, 1.0f);
            ImGui::SliderFloat4("Diffuse", GoldStruct.m_Diffuse, 0.0f, 1.0f);
            ImGui::SliderFloat4("Specular", GoldStruct.m_Specular, 0.0f, 1.0f);
            ImGui::SliderFloat("Shininess", GoldStruct.m_Shininess, 1.0f, 128.0f);

            ImGui::Text("POSITIONAL LIGHT");
            ImGui::Text("Light Position");
            ImGui::SliderFloat3("Position", positionalLightStruct.m_Position, -180.0f, 180.0f);
            ImGui::SliderFloat4("Ambient", positionalLightStruct.m_Ambient, 0.0f, 1.0f);
            ImGui::SliderFloat4("Diffuse", positionalLightStruct.m_Diffuse, 0.0f, 1.0f);
            ImGui::SliderFloat4("Specular", positionalLightStruct.m_Specular, 0.0f, 1.0f);
            ImGui::EndChild();
            ImGui::End();
        }

        GUI.UI_Render();
                   
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}