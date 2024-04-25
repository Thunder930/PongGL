#include "main.h"

int main(int argc, char** argv)
{
    GLFWwindow *window;

    InitGraphics(window);

    glfwSwapBuffers(window);

    Paddle* paddleArray;
    Ball* ballArray;

    Load(paddleArray, ballArray);

    double time = glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Render(paddleArray, ballArray);

        double deltaTime = glfwGetTime() - time;
        time = glfwGetTime();
        Update(window, paddleArray, ballArray, deltaTime);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
  
    }
    UnLoad(paddleArray, ballArray);
    return 0;
}

void processInput(GLFWwindow *window, Paddle *&paddleArray, Ball *&ballArray, double deltaTime) {
    if (state == STARTED) {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            paddleArray[0].up(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            paddleArray[0].down(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            paddleArray[1].up(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            paddleArray[1].down(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            for (int i = 0; i < NUM_PADDLES; i++) {
                paddleArray[i].resetPosition();
            }
            for (int i = 0; i < NUM_BALLS; i++) {
                ballArray[i].resetPosition();
            }

            state = STOPPED;
        }
    }
    else {
        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            state = STARTED;
            for (int i = 0; i < NUM_BALLS; i++) {
                ballArray[i].generateVelocity();
            }
        }
    }
}

void Render(Paddle *&paddleArray, Ball *&ballArray)
{
    for (int i = 0; i < NUM_PADDLES; i++) {
        paddleArray[i].Render();
    }
    for (int i = 0; i < NUM_BALLS; i++) {
        ballArray[i].Render();
    }

}

void InitGraphics(GLFWwindow *&window) {
    /* Initialize the library */
    if (!glfwInit()) {
        fprintf(stderr, "Error: failed to initalize GLEW");
        exit(-1);
    }
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Pong", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Error: failed to create window");
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        exit(-1);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

}

void Load(Paddle *&paddleArray, Ball *&ballArray) {
    Paddle leftPaddle(-0.7f, 0.5f);
    Paddle rightPaddle(0.7f, 0.5f);
    Ball ball(0.0f, 0.5f);
    paddleArray = (Paddle*)malloc(NUM_PADDLES * sizeof(Paddle));
    if (!paddleArray)
    {
        fprintf(stderr, "Error: Failed to get memory for paddles");
        UnLoad();
        exit(-1);
    }
    ballArray = (Ball*)malloc(NUM_BALLS * sizeof(Ball));
    if (!ballArray)
    {
        fprintf(stderr, "Error: Failed to get memory for balls");
        UnLoad(paddleArray);
        exit(-1);
    }
    paddleArray[0] = leftPaddle;
    paddleArray[1] = rightPaddle;
    ballArray[0] = ball;
}

void UnLoad() {
    glfwTerminate();
}

void UnLoad(Paddle*& paddleArray) {
    free(paddleArray);
    glfwTerminate();
}

void UnLoad(Paddle *&paddleArray, Ball *&ballArray) {
    free(paddleArray);
    free(ballArray);
    glfwTerminate();
}

void Update(GLFWwindow *&window, Paddle *&paddleArray, Ball *&ballArray, double deltaTime) {
    for (int i = 0; i < NUM_BALLS; i++) {
        ballArray[i].Move(deltaTime, paddleArray);
        processInput(window, paddleArray, ballArray, deltaTime);
    }
}