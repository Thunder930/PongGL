#include "Paddle.h"

Paddle::Paddle(float xPos, float yPos)
{
	// Top Left
	positions[0] = xPos - PADDLE_HALF_WIDTH; 
	positions[1] = yPos + PADDLE_HALF_HEIGHT;
	// Top Right
	positions[2] = xPos + PADDLE_HALF_WIDTH;
	positions[3] = yPos + PADDLE_HALF_HEIGHT;
	// Bottom Left
	positions[4] = xPos - PADDLE_HALF_WIDTH;
	positions[5] = yPos - PADDLE_HALF_HEIGHT;
	// Bottom Right
	positions[6] = xPos + PADDLE_HALF_WIDTH;
	positions[7] = yPos - PADDLE_HALF_HEIGHT;

	Render();
}

void Paddle::up(double deltaTime)
{
	if (positions[5] <= 1.0f) {
		positions[1] += (float)(2 * deltaTime);
		positions[3] += (float)(2 * deltaTime);
		positions[5] += (float)(2 * deltaTime);
		positions[7] += (float)(2 * deltaTime);
	}
}

void Paddle::down(double deltaTime)
{
	if (positions[1] >= -1.0f) {
		positions[1] -= (float)(2 * deltaTime);
		positions[3] -= (float)(2 * deltaTime);
		positions[5] -= (float)(2 * deltaTime);
		positions[7] -= (float)(2 * deltaTime);
	}
}

void Paddle::Render()
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

void Paddle::getDimensions(float &left, float &right, float &top, float &bottom)
{
	left = positions[0];
	right = positions[2];
	top = positions[1];
	bottom = positions[5];
}
