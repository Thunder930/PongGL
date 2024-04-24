#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Paddle.h>

class Ball
{
public:
	Ball(float xPos, float yPos);
	void Render();
	void Move(double deltaTime, Paddle* paddles[2], int numPaddles);
	void generateVelocity();
	bool isColliding(Paddle** paddles, int numPaddles);

private:
	float positions[8];
	double xVelocity;
	double yVelocity;
};

