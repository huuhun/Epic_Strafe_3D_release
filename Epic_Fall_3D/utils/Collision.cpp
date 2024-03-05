#include <iostream>
#include "Collision.h"
bool checkCollision(const glm::vec3& pos1, const glm::vec3& pos2)
{
	// Assuming cube size is 1x1x1 for simplicity
	float size = 1.0f;

	// Calculate the minimum and maximum coordinates of the bounding boxes
	glm::vec3 min1 = pos1 - glm::vec3(size / 2.5f);
	glm::vec3 max1 = pos1 + glm::vec3(size / 2.5f);
	glm::vec3 min2 = pos2 - glm::vec3(size / 2.5f);
	glm::vec3 max2 = pos2 + glm::vec3(size / 2.5f);

	// Check for collision along each axis
	bool collisionX = min1.x < max2.x && max1.x > min2.x;
	bool collisionY = min1.y < max2.y && max1.y > min2.y;
	bool collisionZ = min1.z < max2.z && max1.z > min2.z;


	// Check if there is a collision in all three axes
	return collisionX && collisionY && collisionZ;
}

bool isCollidingWithPlane(const float cubeVertices[], int numVertices, float planeConstant) {
	// Assuming cubeVertices format is: x, y, z, textureX, textureY
	const int vertexSize = 5; // Assuming 5 values per vertex

	// Calculate the center of the cube
	float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
	for( int i = 0; i < numVertices; i += vertexSize ) {
		centerX += cubeVertices[ i ];
		centerY += cubeVertices[ i + 1 ];
		centerZ += cubeVertices[ i + 2 ];
	}
	centerX /= ( numVertices / vertexSize );
	centerY /= ( numVertices / vertexSize );
	centerZ /= ( numVertices / vertexSize );

	// Check each vertex against the plane
	for( int i = 0; i < numVertices; i += vertexSize ) {
		float x = cubeVertices[ i ];
		float y = cubeVertices[ i + 1 ];
		float z = cubeVertices[ i + 2 ];

		// Calculate the signed distance from the plane
		float distance = x + y + planeConstant;

		// Check if the cube is on the opposite side of the plane from its center
		if( ( distance > 0.0f && centerZ <= planeConstant ) || ( distance < 0.0f && centerZ >= planeConstant ) ) {
			std::cout << "Collision detected!" << std::endl;
			return true;
		}
	}

	// No collision detected
	std::cout << "No collision." << std::endl;
	return false;
}
