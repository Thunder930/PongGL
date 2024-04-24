#include "Ball.h"
#include <time.h>
#include <cstdlib>

Ball::Ball(float xPos, float yPos)
{
	// Top Left
	positions[0] = xPos - 0.03f;
	positions[1] = yPos + 0.03f;
	// Top Right
	positions[2] = xPos + 0.03f;
	positions[3] = yPos + 0.03f;
	// Bottom Left
	positions[4] = xPos - 0.03f;
	positions[5] = yPos - 0.03f;
	// Bottom Right
	positions[6] = xPos + 0.03f;
	positions[7] = yPos - 0.03f;

	xVelocity = 0.0;
	yVelocity = 0.0;

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

void Ball::Move(double deltaTime, float leftDimensions[], float rightDimensions[])
{
	if (positions[1] >= 1.0f || positions[5] <= -1.0f) {
		yVelocity = -yVelocity;
	}
	// (Left of Ball <= Right of LPaddle && Bottom of Ball <= Top of LPaddle && Top of Ball >= Bottom of LPaddle) || (Right of Ball >= Left of RPaddle && Bottom of Ball <= Top of RPaddle && Top of Ball >= Bottom of RPaddle)
	if ((positions[4] <= leftDimensions[1] && positions[5] <= leftDimensions[2] && positions[1] >= leftDimensions[3]) || (positions[6] >= rightDimensions[0] && positions[5] <= rightDimensions[2] && positions[1] >= rightDimensions[3])) {
		xVelocity = -xVelocity;
		yVelocity = -yVelocity;
	}
	positions[0] += (float)(xVelocity * deltaTime);
	positions[2] += (float)(xVelocity * deltaTime);
	positions[4] += (float)(xVelocity * deltaTime);
	positions[6] += (float)(xVelocity * deltaTime);

	positions[7] += (float)(yVelocity * deltaTime);
	positions[1] += (float)(yVelocity * deltaTime);
	positions[3] += (float)(yVelocity * deltaTime);
	positions[5] += (float)(yVelocity * deltaTime);
}

void Ball::generateVelocity()
{
	srand(time(NULL));
	xVelocity = (rand() % 400)/100.0 - 2;
	yVelocity = (rand() % 400)/100.0 - 2;
}
