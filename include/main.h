#pragma once
#include <stdio.h>
#include "Paddle.h"
#include "Ball.h"
#include <malloc.h>
#include <stdlib.h>



GAME_STATE state = STOPPED;

void ProcessInput(GLFWwindow *window, Paddle *&paddleArray, Ball *&ballArray, double deltaTime);
void Render(Paddle *&paddleArray, Ball *&ballArray, int *&scoreArray);
void InitGraphics(GLFWwindow *&window);
void Load(Paddle*& paddleArray, Ball*& ballArray, int *&scoreArray);
void UnLoad();
void UnLoad(int*& scoreArray);
void UnLoad(int*& scoreArray, Paddle*& paddleArray);
void UnLoad(int*& scoreArray, Paddle*& paddleArray, Ball*& ballArray);
void Update(GLFWwindow*& window, Paddle *&paddleArray, Ball *&ballArray, int *&scoreArray, double deltaTime);
void DrawBoundingLine(float yPos);
void DrawNumber(int num, float xPos);