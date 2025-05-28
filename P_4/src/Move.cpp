#include "Move.h"
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include <iostream>

Move::Move(const double seconds, float* movespeed, glm::vec3* position):intervalSeconds(seconds)
{
	if (movespeed == nullptr)
	{
		movespeed = new float(0.0f);
	}

	std::thread inputThread(&Move::Input, position, movespeed);
	std::this_thread::sleep_for(std::chrono::milliseconds((long)intervalSeconds * 1000));
	inputThread.detach();

}


void Move::Input(glm::vec3* position, const float* speed)
{
	if (GetAsyncKeyState(65) & GetAsyncKeyState(VK_RBUTTON)) //A	
		position->x -= *speed;
		
	else if (GetAsyncKeyState(68) & GetAsyncKeyState(VK_RBUTTON)) //D
		position->x += *speed;
	
	else if (GetAsyncKeyState(87) & GetAsyncKeyState(VK_RBUTTON)) //W
		position->z -= *speed;
		
	else if (GetAsyncKeyState(83) & GetAsyncKeyState(VK_RBUTTON)) //S
		position->z += *speed;

	else if (GetAsyncKeyState(69) & GetAsyncKeyState(VK_RBUTTON)) //E
		position->y += *speed;

	else if (GetAsyncKeyState(81) & GetAsyncKeyState(VK_RBUTTON)) //Q
		position->y -= *speed;
	else
		return;
		
}

