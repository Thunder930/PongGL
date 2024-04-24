#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Paddle.h>
#include <Constants.h>

class Ball
{
public:
	Ball(float xPos, float yPos);
	void Render();
	void Move(double deltaTime, Paddle** paddles, int numPaddles);
	void generateVelocity();
	bool isColliding(Paddle** paddles, int numPaddles);
	void generateVerticies();

private:
	float positions[8];
	float xPos;
	float yPos;
	double xVelocity;
	double yVelocity;
};

