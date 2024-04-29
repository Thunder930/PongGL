#include "main.h"

int main(int argc, char** argv)
{
    GLFWwindow *window;

    InitGraphics(window);

    glfwSwapBuffers(window);

    Paddle* paddleArray;
    Ball* ballArray;
    int* scoreArray;

    Load(paddleArray, ballArray, scoreArray);

    double time = glfwGetTime();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        Render(paddleArray, ballArray, scoreArray);

        double deltaTime = glfwGetTime() - time;
        time = glfwGetTime();
        Update(window, paddleArray, ballArray, scoreArray, deltaTime);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
  
    }
    UnLoad(scoreArray, paddleArray, ballArray);
    return 0;
}

void ProcessInput(GLFWwindow *window, Paddle *&paddleArray, Ball *&ballArray, double deltaTime) {
    if (state == STARTED) {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            paddleArray[0].Up(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            paddleArray[0].Down(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            paddleArray[1].Up(deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            paddleArray[1].Down(deltaTime);
        }
    }
    else {
        if (glfwGetKey(window, GLFW_KEY_SPACE)) {
            state = STARTED;
            for (int i = 0; i < NUM_BALLS; i++) {
                ballArray[i].GenerateVelocity();
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        state = RESET;
    }
}

void Render(Paddle *&paddleArray, Ball *&ballArray, int *&scoreArray)
{
    for (int i = 0; i < NUM_PADDLES; i++) {
        paddleArray[i].Render();
    }
    for (int i = 0; i < NUM_BALLS; i++) {
        ballArray[i].Render();
    }
    for (int i = -3; i < 4; i++) {
        DrawBoundingLine(i/4.0f);
    }
    DrawNumber(scoreArray[0], -0.3f);
    DrawNumber(scoreArray[1], 0.3f);
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

void Load(Paddle *&paddleArray, Ball *&ballArray, int *&scoreArray) {

    scoreArray = (int*)calloc(NUM_PADDLES, sizeof(int));
    if (!scoreArray) {
        fprintf(stderr, "Error: Failed to get memory for scores");
        UnLoad();
        exit(-1);
    }

    paddleArray = (Paddle*)malloc(NUM_PADDLES * sizeof(Paddle));
    if (!paddleArray)
    {
        fprintf(stderr, "Error: Failed to get memory for paddles");
        UnLoad(scoreArray);
        exit(-1);
    }
    Paddle leftPaddle(-0.7f, 0.5f);
    Paddle rightPaddle(0.7f, 0.5f);
    ballArray = (Ball*)malloc(NUM_BALLS * sizeof(Ball));
    if (!ballArray)
    {
        fprintf(stderr, "Error: Failed to get memory for balls");
        UnLoad(scoreArray, paddleArray);
        exit(-1);
    }
    Ball ball(0.0f, 0.5f, scoreArray);
    paddleArray[0] = leftPaddle;
    paddleArray[1] = rightPaddle;
    ballArray[0] = ball;
}

void UnLoad() {
    glfwTerminate();
}

void UnLoad(int *&scoreArray) {
    free(scoreArray);
    glfwTerminate();
}

void UnLoad(int *&scoreArray, Paddle *&paddleArray) {
    free(scoreArray);
    free(paddleArray);
    glfwTerminate();
}

void UnLoad(int *&scoreArray, Paddle *&paddleArray, Ball *&ballArray) {
    free(scoreArray);
    free(paddleArray);
    free(ballArray);
    glfwTerminate();
}

void Update(GLFWwindow *&window, Paddle *&paddleArray, Ball *&ballArray, int *&scoreArray, double deltaTime) {
    if (state == RESET) {
        for (int i = 0; i < NUM_PADDLES; i++) {
            paddleArray[i].ResetPosition();
        }
        for (int i = 0; i < NUM_BALLS; i++) {
            ballArray[i].ResetPosition();
        }
        for (int i = 0; i < NUM_PADDLES; i++) {
            scoreArray[i] = 0;

        }
        state = STOPPED;
    }
    if (state == STOPPED) {
        for (int i = 0; i < NUM_BALLS; i++) {
            ballArray[i].ResetPosition();
        }
    }
    if (state == STARTED) {
        for (int i = 0; i < NUM_BALLS; i++) {
            ballArray[i].Move(deltaTime, paddleArray, state);
        }
    }
    ProcessInput(window, paddleArray, ballArray, deltaTime);
}

void DrawBoundingLine(float yPos) {
    glBegin(GL_TRIANGLES);
    // Triangle #1
    // Top Left
    glVertex2f(-DIVIDING_LINE_HALF_WIDTH, yPos + DIVIDING_LINE_HALF_HEIGHT);
    // Top Right
    glVertex2f(DIVIDING_LINE_HALF_WIDTH, yPos + DIVIDING_LINE_HALF_HEIGHT);
    // Bottom Left
    glVertex2f(-DIVIDING_LINE_HALF_WIDTH, yPos - DIVIDING_LINE_HALF_HEIGHT);

    // Triangle #2
    // Top Right
    glVertex2f(DIVIDING_LINE_HALF_WIDTH, yPos + DIVIDING_LINE_HALF_HEIGHT);
    // Bottom Left
    glVertex2f(-DIVIDING_LINE_HALF_WIDTH, yPos - DIVIDING_LINE_HALF_HEIGHT);
    // Bottom Right
    glVertex2f(DIVIDING_LINE_HALF_WIDTH, yPos - DIVIDING_LINE_HALF_HEIGHT);

    glEnd();
}

void DrawNumber(int num, float xPos) {

    // An attempt at a seven segment display. This should probably be refactored to use a multi-level array,
    // with each number pointing to the needed segments.

    // Also, this headache is why you would use sprites in a serious application.

    glBegin(GL_TRIANGLES);

    uint8_t segments = 0b00000000;

    switch (num) {
    case 0:
        segments = 0b11111100;
        break;
    case 1: 
        segments = 0b00011000;
        break;
    case 2:
        segments = 0b01101110;
        break;
    case 3:
        segments = 0b00111110;
        break;
    case 4:
        segments = 0b10011010;
        break;
    case 5:
        segments = 0b10110110;
        break;
    case 6:
        segments = 0b11110110;
        break;
    case 7:
        segments = 0b00011100;
        break;
    case 8:
        segments = 0b11111110;
        break;
    case 9:
        segments = 0b10011110;
        break;
    }

    // Upper Left Segment
    if (segments & 0b10000000) {
        glVertex2f(xPos - 0.1f, 0.8f);
        glVertex2f(xPos - 0.05f, 0.8f);
        glVertex2f(xPos - 0.1f, 0.65f);

        glVertex2f(xPos - 0.1f, 0.65f);
        glVertex2f(xPos - 0.05f, 0.8f);
        glVertex2f(xPos - 0.05f, 0.65f);
    }
    // Lower Left Segment
    if (segments & 0b01000000) {
        glVertex2f(xPos - 0.1f, 0.65f);
        glVertex2f(xPos - 0.05f, 0.65f);
        glVertex2f(xPos - 0.1f, 0.5f);

        glVertex2f(xPos - 0.1f, 0.5f);
        glVertex2f(xPos - 0.05f, 0.65f);
        glVertex2f(xPos - 0.05f, 0.5f);
    }
    // Lower Segment
    if (segments & 0b00100000) {
        glVertex2f(xPos - 0.1f, 0.5f);
        glVertex2f(xPos + 0.1f, 0.5f);
        glVertex2f(xPos + 0.1f, 0.45f);

        glVertex2f(xPos - 0.1f, 0.5f);
        glVertex2f(xPos + 0.1f, 0.45f);
        glVertex2f(xPos - 0.1f, 0.45f);
    }
    // Lower Right Segment
    if (segments & 0b00010000) {
        glVertex2f(xPos + 0.05f, 0.5f);
        glVertex2f(xPos + 0.1f, 0.5f);
        glVertex2f(xPos + 0.05f, 0.65f);

        glVertex2f(xPos + 0.05f, 0.65f);
        glVertex2f(xPos + 0.1f, 0.65f);
        glVertex2f(xPos + 0.1f, 0.5f);
    }
    // Upper Right Segment
    if (segments & 0b00001000) {
        glVertex2f(xPos + 0.05f, 0.65f);
        glVertex2f(xPos + 0.1f, 0.65f);
        glVertex2f(xPos + 0.05f, 0.8f);

        glVertex2f(xPos + 0.05f, 0.8f);
        glVertex2f(xPos + 0.1f, 0.8f);
        glVertex2f(xPos + 0.1f, 0.65f);
    }
    // Upper Segment
    if (segments & 0b00000100) {
        glVertex2f(xPos - 0.1f, 0.8f);
        glVertex2f(xPos + 0.1f, 0.8f);
        glVertex2f(xPos + 0.1f, 0.75f);

        glVertex2f(xPos - 0.1f, 0.8f);
        glVertex2f(xPos + 0.1f, 0.75f);
        glVertex2f(xPos - 0.1f, 0.75f);
    }
    // Middle Segment
    if (segments & 0b00000010) {
        glVertex2f(xPos - 0.1f, 0.65f);
        glVertex2f(xPos + 0.1f, 0.65f);
        glVertex2f(xPos + 0.1f, 0.6f);

        glVertex2f(xPos - 0.1f, 0.65f);
        glVertex2f(xPos + 0.1f, 0.6f);
        glVertex2f(xPos - 0.1f, 0.6f);
    }

    glEnd();
}