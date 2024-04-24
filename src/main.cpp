#include <stdio.h>
#include "Paddle.h"
#include "Ball.h"
#include <malloc.h>

const int NUM_PADDLES = 2;
enum GAME_STATE { STOPPED, STARTED };

GAME_STATE state = STOPPED;

void processInput(GLFWwindow* window, Paddle** paddleArray, Ball* ball, double deltaTime);

int main(int argc, char** argv)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Pong", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    glfwSwapBuffers(window);

    Paddle leftPaddle(-0.7f, 0.5f);
    Paddle rightPaddle(0.7f, 0.5f);
    Ball ball(0.0f, 0.5f);
    Paddle** paddleArray = (Paddle**)malloc(NUM_PADDLES * sizeof(Paddle));
    if (!paddleArray) 
    {
        glfwTerminate();
        return -1;
    }
    paddleArray[0] = &leftPaddle;
    paddleArray[1] = &rightPaddle;

    double time = glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        double deltaTime = glfwGetTime() - time;
        time = glfwGetTime();

        leftPaddle.Render();
        rightPaddle.Render();


        ball.Move(deltaTime, paddleArray, NUM_PADDLES);
        ball.Render();

        processInput(window, paddleArray, &ball, deltaTime);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
  
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Paddle** paddleArray, Ball* ball, double deltaTime) {
    if (state == STARTED) {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            paddleArray[0]->up(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            paddleArray[0]->down(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            paddleArray[1]->up(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            paddleArray[1]->down(deltaTime);
        }
    }
    else {
        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            state = STARTED;
            ball->generateVelocity();
        }
    }
}