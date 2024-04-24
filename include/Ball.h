#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Ball
{
public:
	Ball(float xPos, float yPos);
	void Render();
	void Move(double deltaTime, float leftDimensions[], float rightDimwnsions[]);
	void generateVelocity();

private:
	float positions[8];
	double xVelocity;
	double yVelocity;
};

