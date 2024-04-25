#pragma once
#include <stdio.h>
#include "Paddle.h"
#include "Ball.h"
#include <malloc.h>
#include <stdlib.h>

enum GAME_STATE { STOPPED, STARTED };

GAME_STATE state = STOPPED;

void ProcessInput(GLFWwindow *window, Paddle *&paddleArray, Ball *&ballArray, double deltaTime);
void Render(Paddle *&paddleArray, Ball *&ballArray);
void InitGraphics(GLFWwindow *&window);
void Load(Paddle *&paddleArray, Ball *&ballArray);
void UnLoad();
void UnLoad(Paddle *&paddleArray);
void UnLoad(Paddle *&paddleArray, Ball *&ballArray);
void Update(GLFWwindow*& window, Paddle *&paddleArray, Ball *&ballArray, double deltaTime);