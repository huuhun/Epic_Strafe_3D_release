#include <iostream>
#include <vector>
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

bool checkBoundaryCollision(const glm::vec3& cameraPosition, const float boundaryVertices[]) {
    for( int i = 0; i < 36; i += 18 ) {
        float minX = boundaryVertices[ i ];
        float maxX = boundaryVertices[ i ];
        float minY = boundaryVertices[ i + 1 ];
        float maxY = boundaryVertices[ i + 1 ];
        float minZ = boundaryVertices[ i + 2 ];
        float maxZ = boundaryVertices[ i + 2 ];

        // Calculate the bounding box for each face
        for( int j = i + 3; j < i + 18; j += 3 ) {
            float x = boundaryVertices[ j ];
            float y = boundaryVertices[ j + 1 ];
            float z = boundaryVertices[ j + 2 ];

            minX = std::min(minX, x);
            maxX = std::max(maxX, x);
            minY = std::min(minY, y);
            maxY = std::max(maxY, y);
            minZ = std::min(minZ, z);
            maxZ = std::max(maxZ, z);
        }

        // Check if the camera position is inside the bounding box of the current face
        if( cameraPosition.x >= minX && cameraPosition.x <= maxX &&
           cameraPosition.y >= minY && cameraPosition.y <= maxY &&
           cameraPosition.z >= minZ && cameraPosition.z <= maxZ ) {
            std::cout << "Camera inside the boundary." << std::endl;
            return true;
        }
    }

    std::cout << "Camera outside the boundary." << std::endl;
    return false;
}

// Function to check if the camera is colliding with any of the cubes
bool isCameraColliding(const glm::vec3& cameraPosition, const std::vector<glm::vec3>& cubePositions, const glm::vec3& cubeSize) {
    for( const auto& cubePos : cubePositions ) {
        if( cameraPosition.x >= cubePos.x - cubeSize.x && cameraPosition.x <= cubePos.x + cubeSize.x &&
           cameraPosition.y >= cubePos.y - cubeSize.y && cameraPosition.y <= cubePos.y + cubeSize.y &&
           cameraPosition.z >= cubePos.z - cubeSize.z && cameraPosition.z <= cubePos.z + cubeSize.z ) {
            std::cout << "Camera colliding with cube at (" << cubePos.x << ", " << cubePos.y << ", " << cubePos.z << ")\n";
            return true;
        }
    }

    std::cout << "Camera not colliding with any cubes.\n";
    return false;
}


