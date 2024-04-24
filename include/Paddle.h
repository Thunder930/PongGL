#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Constants.h>

class Paddle
{
public:
	Paddle(float xPos, float yPos);
	void up(double deltaTime);
	void down(double deltaTime);
	void Render();
	void getDimensions(float& left, float& right, float& top, float& bottom);
	void generateVerticies();

private:
	float positions[8];
	float xPos;
	float yPos;
};

