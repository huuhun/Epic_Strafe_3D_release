#include <iostream>
#include "Settings.h"
#include "Spawner.h"

std::vector<glm::vec3> spawnObstacles(const unsigned& posAmount)
{
	std::vector<glm::vec3> cubePos = { glm::vec3(0.0f,  0.0f,  0.0f), };

	for( int i = 0; i < posAmount; i++ )
	{
		float x = getRandomNum(-5.0f, 5.0f);
		float y = getRandomNum(-5.0f, 5.0f);
		float rangeBetween = getRandomNum(1.0f, 3.0f);
		float z = getRandomNum(cubePos.at(i).z - rangeBetween, cubePos.at(i).z);
		std::cout << z << "\n";
		cubePos.push_back(glm::vec3(x, y, z));
	}
	return cubePos;
}

void spawnBoundariesVector(std::vector<glm::vec3>& leftBoundaryPos,
						   std::vector<glm::vec3>& rightBoundaryPos, 
						   std::vector<glm::vec3>& topBoundaryPos, 
						   std::vector<glm::vec3>& bottomBoundaryPos) {

	for( int i = 0; i < MAX_BOUNDARIES; i++ )
	{
		if( i == 0 )
		{
			leftBoundaryPos.push_back(spawnBoundary(-5.0f, 5.0f, 2.3f));
			rightBoundaryPos.push_back(spawnBoundary(75.0f, 5.0f, 7.5f));
			topBoundaryPos.push_back(spawnBoundary(36.0f, 44.0f, 5.5f));
			bottomBoundaryPos.push_back(spawnBoundary(36.0f, -35.0f, 5.5f));
		}
		else
		{
			leftBoundaryPos.push_back(spawnBoundary(-5.0f, 5.0f,
													leftBoundaryPos.at(i - 1).z + 2.3f));

			rightBoundaryPos.push_back(spawnBoundary(75.0f, 5.0f,
													 rightBoundaryPos.at(i - 1).z + 7.5f));

			topBoundaryPos.push_back(spawnBoundary(36.0f, 44.0f,
												   rightBoundaryPos.at(i - 1).z + 5.5f));

			bottomBoundaryPos.push_back(spawnBoundary(36.0f, -35.0f,
													  bottomBoundaryPos.at(i - 1).z + 5.5f));
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
			cubePos.at(i).z += -60.0f;
			cubePos.at(i).x = getRandomNum(-5.0f, 5.0f);
			cubePos.at(i).y = getRandomNum(-5.0f, 5.0f);
		}
	}

}

void reallocateBoundary(glm::vec3& cubePos, const unsigned& verticesAmount, Camera& camera, Shader& shader, Renderer& renderer)
{

	if( camera.Position.z > cubePos.z - 5.0f )
	{
		Model cubeModel;
		cubeModel.setTranslation(cubePos);
		float angle{ 94.0f };
		cubeModel.setFixedModelRotation(angle, glm::vec3(0.0f, -1.0f, 0.0f));
		shader.setMat4("model", cubeModel.getModel());
		renderer.DrawArrays(verticesAmount);
	}
	else
		cubePos.z += -60.0f;

}
