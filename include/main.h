#pragma once
#include <stdio.h>
#include "Paddle.h"
#include "Ball.h"
#include <malloc.h>
#include <stdlib.h>

enum GAME_STATE { STOPPED, STARTED };

GAME_STATE state = STOPPED;

void processInput(GLFWwindow *window, Paddle *&paddleArray, Ball *&ball, double deltaTime);
void Render(Paddle *&paddles, Ball *&ballArray);
void InitGraphics(GLFWwindow *&window);
void Load(Paddle *&paddleArray, Ball *&ballArray);
void UnLoad();
void UnLoad(Paddle*& paddleArray);
void UnLoad(Paddle*& paddleArray, Ball*& ballArray);
void Update(GLFWwindow*& window, Paddle*& paddleArray, Ball*& ballArray, double deltaTime);