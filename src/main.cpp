#include <stdio.h>
#include "Paddle.h"
#include "Ball.h"

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

    Paddle leftPaddle(-0.7f, 0.5f);
    Paddle rightPaddle(0.7f, 0.5f);
    Ball ball(0.0f, 0.5f);

    glfwSwapBuffers(window);

    Paddle* paddleArray[3] = {&leftPaddle, &rightPaddle};

    double time = glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        double deltaTime = glfwGetTime() - time;
        time = glfwGetTime();

        leftPaddle.Render();
        rightPaddle.Render();
        float leftDimensions[4] = { 0 };
        float rightDimensions[4]{ 0 };
        leftPaddle.getDimensions(leftDimensions[0], leftDimensions[1], leftDimensions[2], leftDimensions[3]);
        rightPaddle.getDimensions(rightDimensions[0], rightDimensions[1], rightDimensions[2], rightDimensions[3]);
        ball.Move(deltaTime, leftDimensions, rightDimensions);
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