#include <iostream>
#include <vector>
#include <array>
#include <thread>
#include <functional>

#include <glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include "Settings.h"
#include "Calculator.h"
#include "Controller.h"
#include "Spawner.h"

#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Debugger.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Transform.h"
#include "Model.h"
#include "Camera.h"
#include "Collision.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WindowSettings::SCR_WIDTH / 2.0f;
float lastY = WindowSettings::SCR_HEIGHT / 2.0f;
bool firstMouse = true;

int main(int argc, char* args[]) {

	if( !Window::initGLFW() ) return -1;
	GLFWwindow* window{ Window::createGLWindow("Epic Fall 3D", WindowSettings::SCR_WIDTH, WindowSettings::SCR_HEIGHT) };
	Window::createGLContext(window);
	Window::loadGLFunctionPointers();
	Window::setGLVersion(4);
	Window::getGLVersion();

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST); // REMOVE THIS IF DRAW 2D ONLY
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //disable mouse here
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//   0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	//   0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//  -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//  -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	//};

	float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	float boundaryVertices[] = {
		// Front face:
	-20.5f, -20.5f, -20.5f,  0.0f, 0.0f,
	 20.5f, -20.5f, -20.5f,  1.0f, 0.0f,
	 20.5f,  20.5f, -20.5f,  1.0f, 1.0f,
	 20.5f,  20.5f, -20.5f,  1.0f, 1.0f,
	-20.5f,  20.5f, -20.5f,  0.0f, 1.0f,
	-20.5f, -20.5f, -20.5f,  0.0f, 0.0f,

	-20.5f, -20.5f,  20.5f,  0.0f, 0.0f,
	 20.5f, -20.5f,  20.5f,  1.0f, 0.0f,
	 20.5f,  20.5f,  20.5f,  1.0f, 1.0f,
	 20.5f,  20.5f,  20.5f,  1.0f, 1.0f,
	-20.5f,  20.5f,  20.5f,  0.0f, 1.0f,
	-20.5f, -20.5f,  20.5f,  0.0f, 0.0f,

	-20.5f,  20.5f,  20.5f,  1.0f, 0.0f,
	-20.5f,  20.5f, -20.5f,  1.0f, 1.0f,
	-20.5f, -20.5f, -20.5f,  0.0f, 1.0f,
	-20.5f, -20.5f, -20.5f,  0.0f, 1.0f,
	-20.5f, -20.5f,  20.5f,  0.0f, 0.0f,
	-20.5f,  20.5f,  20.5f,  1.0f, 0.0f,

	 20.5f,  20.5f,  20.5f,  1.0f, 0.0f,
	 20.5f,  20.5f, -20.5f,  1.0f, 1.0f,
	 20.5f, -20.5f, -20.5f,  0.0f, 1.0f,
	 20.5f, -20.5f, -20.5f,  0.0f, 1.0f,
	 20.5f, -20.5f,  20.5f,  0.0f, 0.0f,
	 20.5f,  20.5f,  20.5f,  1.0f, 0.0f,

	-20.5f, -20.5f, -20.5f,  0.0f, 1.0f,
	 20.5f, -20.5f, -20.5f,  1.0f, 1.0f,
	 20.5f, -20.5f,  20.5f,  1.0f, 0.0f,
	 20.5f, -20.5f,  20.5f,  1.0f, 0.0f,
	-20.5f, -20.5f,  20.5f,  0.0f, 0.0f,
	-20.5f, -20.5f, -20.5f,  0.0f, 1.0f,

	-20.5f,  20.5f, -20.5f,  0.0f, 1.0f,
	 20.5f,  20.5f, -20.5f,  1.0f, 1.0f,
	 20.5f,  20.5f,  20.5f,  1.0f, 0.0f,
	 20.5f,  20.5f,  20.5f,  1.0f, 0.0f,
	-20.5f,  20.5f,  20.5f,  0.0f, 0.0f,
	-20.5f,  20.5f, -20.5f,  0.0f, 1.0f
	};

	std::vector<glm::vec3> cubePos;
	std::thread spawnObstaclesPosThread([&]() {
		cubePos = spawnObstacles(OBSTACLES_NUM);
										});

	std::vector<glm::vec3> spinCubePos;
	std::thread spawnSpinObstaclesPosThread([&]() {
		spinCubePos = spawnObstacles(SPIN_OBSTACLES_NUM, true);
											});

	std::vector<glm::vec3> spinCubeAxes;
	std::thread spawnSpinObstaclesAxesThread([&]() {
		spinCubeAxes = spawnAxes(SPIN_OBSTACLES_NUM);
											 });

	std::vector<glm::vec3> leftBoundaryPos, rightBoundaryPos, topBoundaryPos, bottomBoundaryPos;
	std::thread spawnBoundariesPosThread([&]() {
		spawnBoundariesVector(leftBoundaryPos, rightBoundaryPos, topBoundaryPos, bottomBoundaryPos);
										 });

	spawnObstaclesPosThread.join();
	spawnSpinObstaclesPosThread.join();
	spawnSpinObstaclesAxesThread.join();
	spawnBoundariesPosThread.join();

	/*unsigned indices[] = {
		0, 1, 3,
		1, 2, 3
	};*/

	VertexArray vao1, vao2;
	VertexBuffer vbo1, vbo2;
	//IndexBuffer ebo;

	vao1.Bind();
	vbo1.Bind();
	vbo1.BufferData(cubeVertices, sizeof(cubeVertices) / sizeof(cubeVertices[ 0 ]));

	// position attribute
	VertexArray::LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	// color attribute
	//VertexArray::LinkAttrib(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)( 3 * sizeof(float) ));
	// texture coord attribute
	//VertexArray::LinkAttrib(2, 2, GL_FLOAT, 8 * sizeof(float), (void*)( 6 * sizeof(float) ));
	// texture coord attribute
	VertexArray::LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)( 3 * sizeof(float) ));

	//ebo.Bind();
	//ebo.BufferData(indices, sizeof(indices) / sizeof(indices[ 0 ]));

	vbo1.Unbind();
	vao1.Unbind();

	vao2.Bind();
	vbo2.Bind();

	vbo2.BufferData(boundaryVertices, sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]));
	VertexArray::LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VertexArray::LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)( 3 * sizeof(float) ));

	vbo2.Unbind();
	vao2.Unbind();

	enableGLDebugContext();

	Shader shader("res/shaders/shader430.vert", "res/shaders/shader430.frag");

	Texture brickWallTexture("res/textures/brick-wall.png");
	Texture faceTexture("res/textures/face.png");
	Texture boundaryTexture("res/textures/boundary.png");

	shader.Use();
	shader.setInt("brickWallTexture", 0);
	shader.setInt("faceTexture", 1);
	shader.setInt("boundaryTexture", 2);

	Renderer renderer;
	renderer.setClearColor();

	Transform transformation;
	bool playing = false;

	//glm::vec3 axis(getRandomNum(-0.5f, 0.5f), getRandomNum(-0.5f, 0.5f), getRandomNum(-0.5f, 0.5f));
	while( !glfwWindowShouldClose(window) ) {
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>( glfwGetTime() );
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window, deltaTime, camera);

		if( playing )
		{
			for( unsigned i = 0; i < leftBoundaryPos.size(); ++i ) {
				if( checkCollision(camera.Position, leftBoundaryPos.at(i), 21.0f) ||
				   checkCollision(camera.Position, rightBoundaryPos.at(i), 21.0f) ||
				   checkCollision(camera.Position, topBoundaryPos.at(i), 21.0f) ||
				   checkCollision(camera.Position, bottomBoundaryPos.at(i), 21.0f) )

					std::cout << "Collision detected between the camera and cube " << std::endl;
			}

			for( int i = 0; i < cubePos.size(); ++i ) {
				if( checkCollision(/*playerCubePos */ camera.Position, cubePos.at(i)) )
					std::cout << "Collision detected between the camera and cube " << i << std::endl;
			}

			for( int i = 0; i < spinCubePos.size(); ++i ) {
				if( checkCollision(/*playerCubePos */ camera.Position, spinCubePos.at(i)) )
					std::cout << "Collision detected between the camera and cube " << i << std::endl;
			}
			renderer.Clear();

			boundaryTexture.ActiveTexture(GL_TEXTURE2);
			brickWallTexture.ActiveTexture(GL_TEXTURE0);
			faceTexture.ActiveTexture(GL_TEXTURE1);

			shader.Use();
			transformation.setProjection(camera.Zoom,
										 (float)WindowSettings::SCR_WIDTH / (float)WindowSettings::SCR_HEIGHT, 0.1f, 40.0f);

			shader.setMat4("projection", transformation.getProjection());
			// create transformations
			transformation.setCameraView(camera.GetViewMatrix());
			shader.setMat4("view", transformation.getView());

			vao1.Bind();
			shader.setInt("renderBoundary", 0);//set flag to 0 to render cube
			moveCameraHitbox(camera, shader);
			reallocateObstacles(cubePos, calVertexAmount(sizeof(cubeVertices) / sizeof(cubeVertices[ 0 ]), 5),
								camera, shader, renderer);
			reallocateSpinningObstacles(spinCubePos, calVertexAmount(sizeof(cubeVertices) / sizeof(cubeVertices[ 0 ]), 5),
										camera, shader, renderer, spinCubeAxes);

			vao1.Unbind();

			vao2.Bind();
			shader.setInt("renderBoundary", 1);//set flag to 1 to render boundary
			reallocateBoundary(leftBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
							   camera, shader, renderer);
			reallocateBoundary(topBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
							   camera, shader, renderer);
			reallocateBoundary(rightBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
							   camera, shader, renderer);
			reallocateBoundary(bottomBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
							   camera, shader, renderer);

		}
		renderer.Clear();

		boundaryTexture.ActiveTexture(GL_TEXTURE2);

		shader.Use();
		transformation.setProjection(camera.Zoom,
									 (float)WindowSettings::SCR_WIDTH / (float)WindowSettings::SCR_HEIGHT, 0.1f, 40.0f);

		shader.setMat4("projection", transformation.getProjection());
		// create transformations
		transformation.setCameraView(camera.GetViewMatrix());
		shader.setMat4("view", transformation.getView());

		vao2.Bind();
		shader.setInt("renderBoundary", 1);//set flag to 1 to render boundary
		reallocateBoundary(leftBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
						   camera, shader, renderer);
		reallocateBoundary(topBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
						   camera, shader, renderer);
		reallocateBoundary(rightBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
						   camera, shader, renderer);
		reallocateBoundary(bottomBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
						   camera, shader, renderer);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//cleanup:
	Window::destroyWindow();

	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>( xposIn );
	float ypos = static_cast<float>( yposIn );

	if( firstMouse )
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>( yoffset ));
}