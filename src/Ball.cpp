#include "Ball.h"
#include <time.h>
#include <cstdlib>

Ball::Ball(float xPos, float yPos, int *&scoreArray)
{
	this->xPos = xPos;
	this->yPos = yPos;
	startingX = xPos;
	startingY = yPos;

	GenerateVerticies();
	xVelocity = 0.0;
	yVelocity = 0.0;

	this->scoreArray = scoreArray;
	Render();
}

void Ball::Render()
{
	glBegin(GL_TRIANGLES);

	glVertex2f(positions[0], positions[1]);
	glVertex2f(positions[2], positions[3]);
	glVertex2f(positions[4], positions[5]);

	glVertex2f(positions[2], positions[3]);
	glVertex2f(positions[4], positions[5]);
	glVertex2f(positions[6], positions[7]);

	glEnd();
}

void Ball::Move(double deltaTime, Paddle *&paddleArray, GAME_STATE& state)
{
	if (xPos - BALL_RADIUS >= 1.0f && scoreArray[0] < 9)
	{
		scoreArray[0]++;
		state = STOPPED;
	}
	if (xPos + BALL_RADIUS <= -1.0f && scoreArray[1] < 9)
	{
		scoreArray[1]++;
		state = STOPPED;
	}
	if (positions[1] >= 1.0f || positions[5] <= -1.0f) {
		yVelocity = -yVelocity;
	}
	if (IsColliding(paddleArray)) {
		xVelocity = -xVelocity;
		yVelocity = -yVelocity;
	}
	xPos += (float)(xVelocity * deltaTime);
	yPos += (float)(yVelocity * deltaTime);
	GenerateVerticies();
}

void Ball::GenerateVelocity()
{
	srand(time(NULL));
	xVelocity = (rand() % 400)/100.0 - 2;
	yVelocity = (rand() % 400)/100.0 - 2;
}

bool Ball::IsColliding(Paddle *&paddleArray)
{
	float dimensions[4];
	for (int i = 0; i < NUM_PADDLES; i++) {
		paddleArray[i].GetDimensions(dimensions[0], dimensions[1], dimensions[2], dimensions[3]);
		// (yPos of ball top >= yPos of paddle bottom) && (yPos of ball bottom <= yPos of paddle top)
		bool vertical = (positions[1] >= dimensions[3]) && (positions[5] <= dimensions[2]);
		// (xPos of ball left <= xPos of paddle right) && (xPos of ball right >= xPos of paddle left)
		bool horizontal = (positions[0] <= dimensions[1]) && (positions[2] >= dimensions[0]);

		if (horizontal && vertical) {
				return true;
		}
	}

	return false;
}

void Ball::GenerateVerticies()
{
	// Top Left
	positions[0] = xPos - BALL_RADIUS;
	positions[1] = yPos + BALL_RADIUS;
	// Top Right
	positions[2] = xPos + BALL_RADIUS;
	positions[3] = yPos + BALL_RADIUS;
	// Bottom Left
	positions[4] = xPos - BALL_RADIUS;
	positions[5] = yPos - BALL_RADIUS;
	// Bottom Right
	positions[6] = xPos + BALL_RADIUS;
	positions[7] = yPos - BALL_RADIUS;
}

void Ball::ResetPosition() 
{
	xPos = startingX;
	yPos = startingY;
	xVelocity = 0;
	yVelocity = 0;
	GenerateVerticies();
}
