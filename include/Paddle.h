#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Constants.h>

class Paddle
{
public:
	Paddle(float xPos, float yPos);
	void Up(double deltaTime);
	void Down(double deltaTime);
	void Render();
	void GetDimensions(float &left, float &right, float &top, float &bottom);
	void GenerateVerticies();
	void ResetPosition();

private:
	float positions[8];
	float xPos;
	float startingX;
	float yPos;
	float startingY;
};

