#include <iostream>
#include "Controller.h"
void processInput(GLFWwindow* window, float& deltaTime, glm::vec3& cameraPos,
	glm::vec3& cameraFront, glm::vec3& cameraUp)
{
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ) {
        std::cout << "Heyo";
        glfwSetWindowShouldClose(window, true);
    }

    float cameraSpeed = static_cast<float>( 2.5 * deltaTime );
    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
        cameraPos += cameraSpeed * cameraFront;
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
        cameraPos -= cameraSpeed * cameraFront;
    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
