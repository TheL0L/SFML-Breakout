#include "collision.h"

namespace Collision
{
    CollisionResult checkCircleRectangleCollision(
        const sf::Vector2f& circleCenter,
        float circleRadius,
        const sf::Vector2f& rectPos,
        const sf::Vector2f& rectSize)
    {
        CollisionResult result;

        // Find the closest point on the rectangle to the circle center
        float closestX = std::max(rectPos.x, std::min(circleCenter.x, rectPos.x + rectSize.x));
        float closestY = std::max(rectPos.y, std::min(circleCenter.y, rectPos.y + rectSize.y));
        sf::Vector2f closestPoint(closestX, closestY);

        // Compute the vector from the closest point to the circle center
        sf::Vector2f collisionVector = circleCenter - closestPoint;
        float distanceSquared = collisionVector.x * collisionVector.x + collisionVector.y * collisionVector.y;

        // Check if a collision occurred
        if (distanceSquared < circleRadius * circleRadius)
        {
            float distance = std::sqrt(distanceSquared);
            if (distance != 0.f)
            {
                result.normal = collisionVector / distance; // Normalize
            }
            else
            {
                result.normal = sf::Vector2f(0.f, -1.f); // Default normal if circle is exactly on the closest point
            }
            result.penetration = circleRadius - distance;
            result.collided = true;
        }

        return result;
    }

    sf::Vector2f reflect(const sf::Vector2f& velocity, const sf::Vector2f& normal)
    {
        return velocity - 2.f * (velocity.x * normal.x + velocity.y * normal.y) * normal;
    }
}
