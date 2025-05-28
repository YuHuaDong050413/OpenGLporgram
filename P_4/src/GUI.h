#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include <ImGui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "Window.h"

class GUI
{
	private:
		GLFWwindow* Window;
	public:
		
		GUI(GLFWwindow* window);
		~GUI();
		WindowSize getWindowSize() const;
		void UI_NewFrame() const;
		void UI_Render() const;
};


