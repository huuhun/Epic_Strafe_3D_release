#include <iostream>
#include "Controller.h"
void processInput(GLFWwindow* window, float& deltaTime, Camera& camera)
{
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ) glfwSetWindowShouldClose(window, true);

    //float cameraSpeed = static_cast<float>( 2.5 * deltaTime );
    //float cameraSpeed = static_cast<float>( 2.5 * deltaTime );

    if( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS )
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if( glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS )
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if( glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )
        camera.ProcessKeyboard(LEFT, deltaTime);
    if( glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
