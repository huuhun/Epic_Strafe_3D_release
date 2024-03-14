#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include "Settings.h"
#include "Spawner.h"

std::vector<glm::vec3> spawnObstacles(const unsigned& posAmount)
{
	std::vector<glm::vec3> cubePos = { glm::vec3(0.0f,  0.0f,  0.0f), };

	for( unsigned i = 0; i < posAmount; i++ )
	{
		float x = getRandomNum(-18.0f, 18.0f);
		float y = getRandomNum(-18.0f, 18.0f);
		float rangeBetween = getRandomNum(1.0f, 8.0f);
		float z = getRandomNum(cubePos.at(i).z - rangeBetween, cubePos.at(i).z);
		cubePos.push_back(glm::vec3(x, y, z));
	}
	return cubePos;
}

std::vector<glm::vec3> spawnObstacles(const unsigned& posAmount, const bool& spinning)
{
	std::vector<glm::vec3> cubePos = { glm::vec3( getRandomNum(-10.0f,10.0f), getRandomNum(-10.0f,10.0f),  0.0f), };

	for( unsigned i = 0; i < posAmount - 1; i++ ) // -1 to avoid posAmount > SPIN_OBSTACLES_NUM by 1
	{
		float x = getRandomNum(-18.0f, 18.0f);
		float y = getRandomNum(-18.0f, 18.0f);
		float rangeBetween = getRandomNum(1.0f, 8.0f);
		float z = getRandomNum(cubePos.at(i).z - rangeBetween, cubePos.at(i).z);
		cubePos.push_back(glm::vec3(x, y, z));
	}
	return cubePos;
}

std::vector<glm::vec3> spawnAxes(const unsigned& axisAmount)
{
	std::vector<glm::vec3> axes;

	for( unsigned i = 0; i < axisAmount; i++ )
	{
		float x = getRandomNum(-0.5f, 0.5f);
		float y = getRandomNum(-0.5f, 0.5f);
		float z = getRandomNum(-0.5f, 0.5f);
		axes.push_back(glm::vec3(x, y, z));
	}
	return axes;
}

void spawnBoundariesVector(std::vector<glm::vec3>& leftBoundaryPos,
						   std::vector<glm::vec3>& rightBoundaryPos,
						   std::vector<glm::vec3>& topBoundaryPos,
						   std::vector<glm::vec3>& bottomBoundaryPos) {

	for( int i = 0; i < MAX_BOUNDARIES; i++ )
	{
		if( i == 0 )
		{
			leftBoundaryPos.push_back(spawnBoundary(-40.0f, 5.0f, 2.3f));
			rightBoundaryPos.push_back(spawnBoundary(40.0f, 5.0f, 2.3f));
			topBoundaryPos.push_back(spawnBoundary(0.0f, 40.0f, 5.5f));
			bottomBoundaryPos.push_back(spawnBoundary(0.0f, -35.0f, 5.5f));
		}
		else
		{
			leftBoundaryPos.push_back(spawnBoundary(leftBoundaryPos.at(i - 1).x /*+ 2.8f*/,
													leftBoundaryPos.at(i - 1).y,
													leftBoundaryPos.at(i - 1).z - 40.0f));

			rightBoundaryPos.push_back(spawnBoundary(rightBoundaryPos.at(i - 1).x,
													 rightBoundaryPos.at(i - 1).y,
													 rightBoundaryPos.at(i - 1).z - 40.0f));

			topBoundaryPos.push_back(spawnBoundary(topBoundaryPos.at(i - 1).x, 
												   topBoundaryPos.at(i - 1).y,
												   topBoundaryPos.at(i - 1).z - 40.0f));

			bottomBoundaryPos.push_back(spawnBoundary(bottomBoundaryPos.at(i - 1).x,
													  bottomBoundaryPos.at(i - 1).y,
													  bottomBoundaryPos.at(i - 1).z - 40.0f));
		}

	}
}

glm::vec3 spawnBoundary(const float& x, const float& y, const float& z)
{
	glm::vec3 cubePos = { glm::vec3(x, y, z), };
	return cubePos;
}

void moveCameraHitbox(Camera& camera, Shader& shader)
{
	Model playerCubeModel;
	playerCubeModel.setTranslation(/*playerCubePos **/ camera.Position);
	float angle{ 0.0f };
	playerCubeModel.setFixedModelRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));
	shader.setMat4("model", playerCubeModel.getModel());
	//renderer.DrawArrays(cal::calVertexAmount(sizeof(vertices) / sizeof(vertices[ 0 ]), 5));
}

void reallocateObstacles(std::vector<glm::vec3>& cubePos, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer)
{
	for( unsigned i = 0; i < cubePos.size(); i++ )
	{
		if( camera.Position.z > cubePos.at(i).z - 5.0f )
		{
			Model cubeModel;
			cubeModel.setTranslation(cubePos.at(i));
			float angle{ 20.0f * (float)i };
			cubeModel.setFixedModelRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", cubeModel.getModel());
			renderer.DrawArrays(verticesAmount);
		}
		else
		{
			cubePos.at(i).z += -70.0f;
			cubePos.at(i).x = getRandomNum(-18.0f, 18.0f);
			cubePos.at(i).y = getRandomNum(-18.0f, 18.0f);
		}
	}

}

void reallocateSpinningObstacles(std::vector<glm::vec3>& cubePos, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer, const std::vector<glm::vec3>& axes)
{
	//glm::vec3 axis(getRandomNum(-0.5f, 0.5f), getRandomNum(-0.5f, 0.5f), getRandomNum(-0.5f, 0.5f));

	for( unsigned i = 0; i < cubePos.size(); i++ )
	{
		if( camera.Position.z > cubePos.at(i).z - 5.0f )
		{
			Model cubeModel;
			cubeModel.setTranslation(cubePos.at(i));
			float angle{ (float)glfwGetTime() * 50.0f };
			cubeModel.setFixedModelRotation(angle, axes.at(i));
			shader.setMat4("model", cubeModel.getModel());
			renderer.DrawArrays(verticesAmount);
		}
		else
		{
			cubePos.at(i).z += -70.0f;
			cubePos.at(i).x = getRandomNum(-18.0f, 18.0f);
			cubePos.at(i).y = getRandomNum(-18.0f, 18.0f);
		}
	}

}


void reallocateBoundary(std::vector<glm::vec3>& cubePos, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer)
{
	//glm::vec3 cubeWithLowestZPos{ getLowestZValue(cubePos) };
	//glm::vec3 cubeWithHighestZPos{ getHighestZValue(cubePos) };

	for( int i = 0; i < cubePos.size(); i++ )
	{
		if( camera.Position.z > cubePos.at(i).z - 60.0f ) //render only
		{
			Model cubeModel;
			cubeModel.setTranslation(cubePos.at(i));
			/*float angle{ 20.0f * (float)i };
			cubeModel.setFixedModelRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));*/

			float angle{ 0.0f };
			cubeModel.setFixedModelRotation(angle, glm::vec3(1.0f, 0.3f, 0.5f));

			/*float angle{ 94.0f };
			cubeModel.setFixedModelRotation(angle, glm::vec3(0.0f, -1.0f, 0.0f));*/

			shader.setMat4("model", cubeModel.getModel());
			renderer.DrawArrays(verticesAmount);
		}
		else // move the cube way further
		{
			//cubePos.at(i) = cubeWithHighestZPos;
			cubePos.at(i).z += /*cubeWithLowestZPos.z*/ - 155.0f;
			//cubePos.at(i).x += 10.0f;
			//cubePos.at(i).y += 5.0f;
			//std::cout << cubeWithLowestZPos.z << "\n";
			/*glm::vec3 cubeWithHighestZPos{ getHighestZValue(cubePos) };
			changeZValueIfItMatch(cubePos, cubeWithHighestZPos, cubeWithHighestZPos.z + 10.0f);*/
		}
	}


}

glm::vec3 getLowestZValue(std::vector<glm::vec3>& cubePos) {
	float currentLowestZ{ cubePos[0].z};
	glm::vec3 cubeWithLowestZValue(0, 0, 0);

	for( unsigned i = 0; i < cubePos.size(); i++ )
		if( cubePos.at(i).z < currentLowestZ ){
			currentLowestZ = cubePos.at(i).z;
			cubeWithLowestZValue = cubePos.at(i);
		}
	
	return cubeWithLowestZValue;
}

glm::vec3 getHighestZValue(std::vector<glm::vec3>& cubePos) {
	float currentHighestZ{ cubePos[ 0 ].z };
	glm::vec3 cubeWithHighestZValue(0,0,0);

	for( int i = 0; i < cubePos.size(); i++ ) {
		if( cubePos.at(i).z < currentHighestZ ) {
			currentHighestZ = cubePos.at(i).z;
			cubeWithHighestZValue = cubePos.at(i);
		}
	}

	return cubeWithHighestZValue;
}
void changeZValueIfItMatch(std::vector<glm::vec3>& cubePos, const glm::vec3& highestZVec3, const float& newZValue) {
	for( auto& vec3 : cubePos ) {

		if( areEqual(vec3.z, highestZVec3.z) ) {
			
			vec3.z = newZValue;
			std::cout << vec3.z << "\n";
		}
		/*else
		{
			std::print("Why?\n");
		}*/

		//break;
	}

}
