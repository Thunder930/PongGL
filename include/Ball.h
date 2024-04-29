#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Paddle.h>
#include <Constants.h>

enum GAME_STATE { STOPPED, STARTED, RESET };

class Ball
{
public:
	Ball(float xPos, float yPos, int *&scoreArray);
	void Render();
	void Move(double deltaTime, Paddle *&paddleArray, GAME_STATE &state);
	void GenerateVelocity();
	bool IsColliding(Paddle *&paddleArray);
	void GenerateVerticies();
	void ResetPosition();

private:
	float positions[8];
	float xPos;
	float startingX;
	float yPos;
	float startingY;
	double xVelocity;
	double yVelocity;
	int *scoreArray;
};

