#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include "utils/Settings.h"
#include "utils/Calculator.h"
#include "utils/Controller.h"

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

	float vertices[] = {
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

	//glm::vec3 playerCubePos{ 0.8f,  0.5f,  0.0f }; //ur cube
	glm::vec3 playerCubePos{ 0.0f, 0.0f, 3.0f };
	// world space positions of our cubes
	glm::vec3 cubePos[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(0.0f,  0.0f,  1.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	/*unsigned indices[] = {
		0, 1, 3,
		1, 2, 3
	};*/

	VertexArray vao;
	VertexBuffer vbo;
	//IndexBuffer ebo;

	vao.Bind();

	vbo.Bind();
	vbo.BufferData(vertices, sizeof(vertices) / sizeof(vertices[ 0 ]));

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

	vbo.Unbind();
	vao.Unbind();

	enableGLDebugContext();

	Shader shader("res/shaders/shader430.vert", "res/shaders/shader430.frag");

	Texture brickWallTexture("res/textures/brick-wall.png");
	Texture faceTexture("res/textures/face.png");

	shader.Use();
	shader.setInt("brickWallTexture", 0);
	shader.setInt("faceTexture", 1);

	Renderer renderer;
	renderer.setClearColor();

	Transform transformation;

	while( !glfwWindowShouldClose(window) ) {
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>( glfwGetTime() );
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//frameStart = SDL_GetTicks();

		processInput(window, deltaTime, camera);
		std::cout << camera.Position.z << "\n";

		for( int i = 0; i < sizeof(cubePos) / sizeof(cubePos[ 0 ]); ++i )
			if( checkCollision(/*playerCubePos * */camera.Position, cubePos[ i ]) )
				std::cout << "Collision detected between the player cube and cube " << i << std::endl;

		renderer.Clear();

		brickWallTexture.ActiveTexture(GL_TEXTURE0);
		faceTexture.ActiveTexture(GL_TEXTURE1);

		shader.Use();
		transformation.setProjection(camera.Zoom,
			(float)WindowSettings::SCR_WIDTH / (float)WindowSettings::SCR_HEIGHT, 0.1f, 100.0f);	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		shader.setMat4("projection", transformation.getProjection());
		// create transformations
		transformation.setCameraView(camera.GetViewMatrix());
		shader.setMat4("view", transformation.getView());

		vao.Bind();

		{
			Model playerCubeModel;
			playerCubeModel.setTranslation(/*playerCubePos **/ camera.Position);
			float angle{ 0.0f };
			playerCubeModel.setFixedModelRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", playerCubeModel.getModel());
			//renderer.DrawArrays(cal::calVertexAmount(sizeof(vertices) / sizeof(vertices[ 0 ]), 5));
		}

		for( unsigned i = 0; i < ( sizeof(cubePos) / sizeof(cubePos[ 0 ]) ); i++ )
		{
			if( camera.Position.z > cubePos[ i ].z - 5.0f   )
			{
				Model cubeModel;
				cubeModel.setTranslation(cubePos[ i ]);
				float angle{ 20.0f * (float)i };
				cubeModel.setFixedModelRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));
				shader.setMat4("model", cubeModel.getModel());
				renderer.DrawArrays(cal::calVertexAmount(sizeof(vertices) / sizeof(vertices[ 0 ]), 5));
			}
		}

		vao.Unbind();

		//Window::capFramerate(frameStart, WindowSettings::MAX_FPS);
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