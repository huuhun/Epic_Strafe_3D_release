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
