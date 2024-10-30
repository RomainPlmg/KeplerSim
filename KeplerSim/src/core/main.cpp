/* clang-format off */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/* clang-format on */

#include "log.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "utils/time.h"
#include "utils/utils.h"

int main(void) {
    // Initialize the logger
    Log::Init();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }
    CORE_INFO("OpenGL initialized");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* clang-format off */
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f,
         1.0f, -1.0f, 0.0f,     1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
         1.0f,  1.0f, 0.0f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,     1.0f, 1.0f, 1.0f,    0.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    /* clang-format on */

    // Create the Vertex Array
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Create the planet texture
    Texture earthTexture(PROJECT_SOURCE_DIR "assets/graphics/sprites/earth.png");
    earthTexture.Bind();

    // Create the shader program
    Shader shader("default", PROJECT_SOURCE_DIR "assets/graphics/shaders/default.vert",
                  PROJECT_SOURCE_DIR "assets/graphics/shaders/default.frag");

    shader.Bind();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(300.0f, 200.0f, 0.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f, 100.0f, 0.0f));
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::ortho(-1280.0f / 2, 1280.0f / 2, 720.0f / 2, -720.0f / 2);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        Time::Update();
        modelMatrix = glm::rotate(modelMatrix,
                                  static_cast<float>(glm::radians(10000.0f) * Time::GetDeltaTime()),
                                  glm::vec3(0.0f, 0.0f, 1.0f));

        shader.SetUniformMat4("model", modelMatrix);
        shader.SetUniformMat4("view", viewMatrix);
        shader.SetUniformMat4("proj", projMatrix);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
