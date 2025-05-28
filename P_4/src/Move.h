#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Move
{
private:
	double intervalSeconds;
	//float  cameraPosX, cameraPosY, cameraPosZ;

	
public:
	Move(const double seconds, float* movespeed, glm::vec3* position);
	//void MoveThread(float* movespeed);
	static void Input(glm::vec3* position, const float* speed);

	/*inline float getPositionX() { return cameraPosX; }
	inline float getPositionY() { return cameraPosY; }
	inline float getPositionZ() { return cameraPosZ; }*/
	//改为回调函数
};