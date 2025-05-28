#include "GUI.h"

GUI::GUI(GLFWwindow* window): Window(window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init();
}
GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

WindowSize GUI::getWindowSize() const
{
    int width, height;
    glfwGetWindowSize(Window, &width, &height);
    return WindowSize(width, height);
}

void GUI::UI_NewFrame() const
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::UI_Render() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

