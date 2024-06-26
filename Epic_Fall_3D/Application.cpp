#include <iostream>
#include <vector>
#include <array>
#include <thread>
#include <functional>
#include <map>

#include <glad/glad.h>
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H  

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
#include "Text.h"
#include "States.h"
#include "Utils.h"
#include "Music.h"
#include "SongPlayer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX{ WindowSettings::SCR_WIDTH / 2.0f };
float lastY{ WindowSettings::SCR_HEIGHT / 2.0f };
bool firstMouse = true;

PlayState state{ PlayState::MENU };

int main(int argc, char* args[]) {

	if( !Window::initGLFW() ) return -1;
	GLFWwindow* window{ Window::createGLWindow("Epic Fall 3D", WindowSettings::SCR_WIDTH, WindowSettings::SCR_HEIGHT) };
	Window::createGLContext(window);
	Window::loadGLFunctionPointers();
	Window::setGLVersion(4);
	Window::getGLVersion();
	Window::setGLGlobalState(window);
	enableGLDebugContext();

	Window::initSDL_Mixer();


	//Callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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

	float enterTextVertices[] = {
	-2.0f, -2.0f, -2.0f,  0.0f, 0.0f,
	 2.0f, -2.0f, -2.0f,  1.0f, 0.0f,
	 2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	 2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	-2.0f,  2.0f, -2.0f,  0.0f, 1.0f,
	-2.0f, -2.0f, -2.0f,  0.0f, 0.0f,

	-2.0f, -2.0f,  2.0f,  0.0f, 0.0f,
	 2.0f, -2.0f,  2.0f,  1.0f, 0.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 1.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 1.0f,
	-2.0f,  2.0f,  2.0f,  0.0f, 1.0f,
	-2.0f, -2.0f,  2.0f,  0.0f, 0.0f,

	-2.0f,  2.0f,  2.0f,  1.0f, 0.0f,
	-2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	-2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	-2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	-2.0f, -2.0f,  2.0f,  0.0f, 0.0f,
	-2.0f,  2.0f,  2.0f,  1.0f, 0.0f,

	 2.0f,  2.0f,  2.0f,  1.0f, 0.0f,
	 2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	 2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	 2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	 2.0f, -2.0f,  2.0f,  0.0f, 0.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 0.0f,

	-2.0f, -2.0f, -2.0f,  0.0f, 1.0f,
	 2.0f, -2.0f, -2.0f,  1.0f, 1.0f,
	 2.0f, -2.0f,  2.0f,  1.0f, 0.0f,
	 2.0f, -2.0f,  2.0f,  1.0f, 0.0f,
	-2.0f, -2.0f,  2.0f,  0.0f, 0.0f,
	-2.0f, -2.0f, -2.0f,  0.0f, 1.0f,

	-2.0f,  2.0f, -2.0f,  0.0f, 1.0f,
	 2.0f,  2.0f, -2.0f,  1.0f, 1.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 0.0f,
	 2.0f,  2.0f,  2.0f,  1.0f, 0.0f,
	-2.0f,  2.0f,  2.0f,  0.0f, 0.0f,
	-2.0f,  2.0f, -2.0f,  0.0f, 1.0f
	};

	float gameOverTextVertices[] = {
	-2.5f, -2.5f, -2.5f,  0.0f, 0.0f,
	 2.5f, -2.5f, -2.5f,  1.0f, 0.0f,
	 2.5f,  2.5f, -2.5f,  1.0f, 1.0f,
	 2.5f,  2.5f, -2.5f,  1.0f, 1.0f,
	-2.5f,  2.5f, -2.5f,  0.0f, 1.0f,
	-2.5f, -2.5f, -2.5f,  0.0f, 0.0f,

	-2.5f, -2.5f,  2.5f,  0.0f, 0.0f,
	 2.5f, -2.5f,  2.5f,  1.0f, 0.0f,
	 2.5f,  2.5f,  2.5f,  1.0f, 1.0f,
	 2.5f,  2.5f,  2.5f,  1.0f, 1.0f,
	-2.5f,  2.5f,  2.5f,  0.0f, 1.0f,
	-2.5f, -2.5f,  2.5f,  0.0f, 0.0f,

	-2.5f,  2.5f,  2.5f,  1.0f, 0.0f,
	-2.5f,  2.5f, -2.5f,  1.0f, 1.0f,
	-2.5f, -2.5f, -2.5f,  0.0f, 1.0f,
	-2.5f, -2.5f, -2.5f,  0.0f, 1.0f,
	-2.5f, -2.5f,  2.5f,  0.0f, 0.0f,
	-2.5f,  2.5f,  2.5f,  1.0f, 0.0f,

	 2.5f,  2.5f,  2.5f,  1.0f, 0.0f,
	 2.5f,  2.5f, -2.5f,  1.0f, 1.0f,
	 2.5f, -2.5f, -2.5f,  0.0f, 1.0f,
	 2.5f, -2.5f, -2.5f,  0.0f, 1.0f,
	 2.5f, -2.5f,  2.5f,  0.0f, 0.0f,
	 2.5f,  2.5f,  2.5f,  1.0f, 0.0f,

	-2.5f, -2.5f, -2.5f,  0.0f, 1.0f,
	 2.5f, -2.5f, -2.5f,  1.0f, 1.0f,
	 2.5f, -2.5f,  2.5f,  1.0f, 0.0f,
	 2.5f, -2.5f,  2.5f,  1.0f, 0.0f,
	-2.5f, -2.5f,  2.5f,  0.0f, 0.0f,
	-2.5f, -2.5f, -2.5f,  0.0f, 1.0f,

	-2.5f,  2.5f, -2.5f,  0.0f, 1.0f,
	 2.5f,  2.5f, -2.5f,  1.0f, 1.0f,
	 2.5f,  2.5f,  2.5f,  1.0f, 0.0f,
	 2.5f,  2.5f,  2.5f,  1.0f, 0.0f,
	-2.5f,  2.5f,  2.5f,  0.0f, 0.0f,
	-2.5f,  2.5f, -2.5f,  0.0f, 1.0f
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

	glm::vec3 enterTextCubePos = spawnText(0.0f, 0.0f, 0.0f);
	glm::vec3 gameOverTextCubePos = spawnText(0.0f, 0.0f, 0.0f);

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

	VertexArray cubeVao, boundaryVao ,enterTextVao, spinCubeVao, gameOverTextVao;
	VertexBuffer cubeVbo, boundaryVbo, enterTextVbo, spinCubeVbo ,gameOverTextVbo;
	//IndexBuffer ebo;

	cubeVao.Bind();
	cubeVbo.Bind();
	cubeVbo.BufferData(cubeVertices, sizeof(cubeVertices) / sizeof(cubeVertices[ 0 ]));

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

	cubeVbo.Unbind();
	cubeVao.Unbind();

	spinCubeVao.Bind();
	spinCubeVbo.Bind();
	spinCubeVbo.BufferData(cubeVertices, sizeof(cubeVertices) / sizeof(cubeVertices[ 0 ]));
	VertexArray::LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VertexArray::LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)( 3 * sizeof(float) ));
	spinCubeVbo.Unbind();
	spinCubeVao.Unbind();

	boundaryVao.Bind();
	boundaryVbo.Bind();

	boundaryVbo.BufferData(boundaryVertices, sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]));
	VertexArray::LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VertexArray::LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)( 3 * sizeof(float) ));

	boundaryVbo.Unbind();
	boundaryVao.Unbind();

	enterTextVao.Bind();
	enterTextVbo.Bind();
	enterTextVbo.BufferData(enterTextVertices, sizeof(enterTextVertices) / sizeof(enterTextVertices[ 0 ]));
	VertexArray::LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VertexArray::LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)( 3 * sizeof(float) ));
	enterTextVbo.Unbind();
	enterTextVao.Unbind();

	gameOverTextVao.Bind();
	gameOverTextVbo.Bind();

	gameOverTextVbo.BufferData(gameOverTextVertices, sizeof(gameOverTextVertices) / sizeof(gameOverTextVertices[ 0 ]));
	VertexArray::LinkAttrib(0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VertexArray::LinkAttrib(1, 2, GL_FLOAT, 5 * sizeof(float), (void*)( 3 * sizeof(float) ));

	gameOverTextVbo.Unbind();
	gameOverTextVao.Unbind();

	

	Shader shader("res/shaders/shader430.vert", "res/shaders/shader430.frag");

	Texture stoneWallTexture("res/textures/stone_wall.png");
	Texture woodWallTexture("res/textures/wood_wall.png");
	Texture faceTexture("res/textures/face.png");
	Texture boundaryTexture("res/textures/boundary.png");
	Texture enterTextBackgroundTexture("res/textures/grey_background.png");
	Texture gameOverTextBackgroundTexture("res/textures/game_over.png");

	shader.Use();
	shader.setInt("stoneWallTexture", 0);
	shader.setInt("faceTexture", 1);
	shader.setInt("woodWallTexture", 2);

	shader.setInt("boundaryTexture", 3);
	shader.setInt("enterTextBackgroundTexture", 4);
	shader.setInt("gameOverTextBackgroundTexture", 5);

	Renderer renderer;
	renderer.setClearColor();

	Transform transformation;

	Music menuMusic("res/musics/menu.wav");
	Music playingMusic("res/musics/playing.wav");
	Music gameOverMusic("res/musics/game_over.wav");
	menuMusic.playMusic();
	SongFlag currentSong{ SongFlag::MENU };

	bool spawnNewEntitiesFlag{ false };

	const float SPEED_INCREMENT{ 0.002f };
	float moventSpeed{ SPEED };

	while( !glfwWindowShouldClose(window) ) {
		// per-frame time logic
		// --------------------
		float currentFrame{ static_cast<float>( glfwGetTime() ) };
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window, deltaTime, camera, state, spawnNewEntitiesFlag);
		//if( songAlreadyStarted ) songAlreadyStarted = false;

		if( spawnNewEntitiesFlag ) spawnNewEntities(cubePos, spinCubePos, spinCubeAxes, leftBoundaryPos, rightBoundaryPos, topBoundaryPos, bottomBoundaryPos);
		
		switch( state )
		{
			case PlayState::PLAYING:
				{
					setSongToPlay(playingMusic, currentSong, SongFlag::PLAYING, setSongToPlayCallback);
					
					float velocity{ moventSpeed * deltaTime  };
					camera.Position += camera.Front * velocity ;
					moventSpeed += SPEED_INCREMENT;

					for( unsigned i = 0; i < leftBoundaryPos.size(); ++i ) {
						if( checkCollision(camera.Position, leftBoundaryPos.at(i), 21.0f) ||
						   checkCollision(camera.Position, rightBoundaryPos.at(i), 21.0f) ||
						   checkCollision(camera.Position, topBoundaryPos.at(i), 21.0f) ||
						   checkCollision(camera.Position, bottomBoundaryPos.at(i), 21.0f) )
						{
							std::cout << "Collision detected between the camera and boundary " << std::endl;
							state = PlayState::GAME_OVER;
						}
					}

					for( int i = 0; i < cubePos.size(); ++i ) {
						if( checkCollision(/*playerCubePos */ camera.Position, cubePos.at(i)) )
						{
							std::cout << "Collision detected between the camera and cube " << i << std::endl;
							state = PlayState::GAME_OVER;
						}
					}

					for( int i = 0; i < spinCubePos.size(); ++i ) {
						if( checkCollision(/*playerCubePos */ camera.Position, spinCubePos.at(i)) ) {
							std::cout << "Collision detected between the camera and cube " << i << std::endl;
							state = PlayState::GAME_OVER;
						}

					}
					renderer.Clear();

					stoneWallTexture.ActiveTexture(GL_TEXTURE0);
					faceTexture.ActiveTexture(GL_TEXTURE1);
					woodWallTexture.ActiveTexture(GL_TEXTURE2);
					boundaryTexture.ActiveTexture(GL_TEXTURE3);

					shader.Use();
					transformation.setProjection(camera.Zoom,
												 (float)WindowSettings::SCR_WIDTH / (float)WindowSettings::SCR_HEIGHT, 0.1f, 50.0f);

					shader.setMat4("projection", transformation.getProjection());
					// create transformations
					transformation.setCameraView(camera.GetViewMatrix());

					shader.setMat4("view", transformation.getView());

					shader.setInt("renderFlag", static_cast<int>( RenderFlag::RenderCube ));
					cubeVao.Bind();
					moveCameraHitbox(camera, shader);
					reallocateObstacles(cubePos, calVertexAmount(sizeof(cubeVertices) / sizeof(cubeVertices[ 0 ]), 5),
										camera, shader, renderer);
					cubeVao.Unbind();

					shader.setInt("renderFlag", static_cast<int>( RenderFlag::RenderSpinCube ));
					spinCubeVao.Bind();
					reallocateSpinningObstacles(spinCubePos, calVertexAmount(sizeof(cubeVertices) / sizeof(cubeVertices[ 0 ]), 5),
												camera, shader, renderer, spinCubeAxes);
					spinCubeVao.Unbind();

					boundaryVao.Bind();
					shader.setInt("renderFlag", static_cast<int>( RenderFlag::RenderBoundary ));//set flag to 1 to render boundary
					reallocateBoundary(leftBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
									   camera, shader, renderer);
					reallocateBoundary(topBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
									   camera, shader, renderer);
					reallocateBoundary(rightBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
									   camera, shader, renderer);
					reallocateBoundary(bottomBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
									   camera, shader, renderer);
					boundaryVao.Unbind();

					break;
				}
			case PlayState::MENU:
				{
					setSongToPlay(playingMusic, currentSong, SongFlag::MENU, setSongToPlayCallback);
					float velocity{ moventSpeed * deltaTime };
					camera.Position += camera.Front * velocity;
					renderer.Clear();

					boundaryTexture.ActiveTexture(GL_TEXTURE3);
					enterTextBackgroundTexture.ActiveTexture(GL_TEXTURE4);
					//gameOverTextBackgroundTexture.ActiveTexture(GL_TEXTURE3);

					shader.Use();
					transformation.setProjection(camera.Zoom,
												 (float)WindowSettings::SCR_WIDTH / (float)WindowSettings::SCR_HEIGHT, 0.1f, 40.0f);

					shader.setMat4("projection", transformation.getProjection());
					// create transformations
					transformation.setCameraView(camera.GetViewMatrix());
					shader.setMat4("view", transformation.getView());

					boundaryVao.Bind();
					shader.setInt("renderFlag", static_cast<int>( RenderFlag::RenderBoundary ));//set flag to 1 to render boundary
					reallocateBoundary(leftBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
									   camera, shader, renderer);
					reallocateBoundary(topBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
									   camera, shader, renderer);
					reallocateBoundary(rightBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
									   camera, shader, renderer);
					reallocateBoundary(bottomBoundaryPos, calVertexAmount(sizeof(boundaryVertices) / sizeof(boundaryVertices[ 0 ]), 5),
									   camera, shader, renderer);
					boundaryVao.Unbind();

					enterTextVao.Bind();
					shader.setInt("renderFlag", static_cast<int>( RenderFlag::RenderEnterText ));
					renderEnterText(enterTextCubePos, calVertexAmount(sizeof(enterTextVertices) / sizeof(enterTextVertices[ 0 ]), 5),
									camera, shader, renderer);

					enterTextVao.Unbind();

					break;
				}
			case PlayState::GAME_OVER:
				{
					setSongToPlay(gameOverMusic, currentSong, SongFlag::GAME_OVER, setSongToPlayCallback);

					renderer.Clear();

					gameOverTextBackgroundTexture.ActiveTexture(GL_TEXTURE5);

					shader.Use();
					transformation.setProjection(camera.Zoom,
												 (float)WindowSettings::SCR_WIDTH / (float)WindowSettings::SCR_HEIGHT, 0.1f, 40.0f);

					shader.setMat4("projection", transformation.getProjection());
					// create transformations
					transformation.setCameraView(camera.GetViewMatrix());
					shader.setMat4("view", transformation.getView());

					gameOverTextVao.Bind();
					shader.setInt("renderFlag", static_cast<int>( RenderFlag::RenderGameOverText ));

					// RESTART GAME
					camera.ResetToDefault();
					restart(cubePos, spinCubePos, spinCubeAxes, leftBoundaryPos, rightBoundaryPos, topBoundaryPos, bottomBoundaryPos, moventSpeed);
					renderGameOverText(gameOverTextCubePos, calVertexAmount(sizeof(gameOverTextVertices) / sizeof(gameOverTextVertices[ 0 ]), 5),
									   camera, shader, renderer);

					gameOverTextVao.Unbind();

					break;
				}
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//cleanup:
	//Window::closeSDL(testText.getFont());
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
	if( state != PlayState::GAME_OVER && state != PlayState::MENU )
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
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if( state != PlayState::GAME_OVER && state != PlayState::MENU )
	{
		camera.ProcessMouseScroll(static_cast<float>( yoffset ));
	}
}

