#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

// Struct to hold collision data
struct CollisionResult
{
    bool collided;
    sf::Vector2f normal;
    float penetration;

    CollisionResult() : collided(false), normal(0.f, 0.f), penetration(0.f) {}
};

namespace Collision
{
    // Check collision between a circle and a rectangle
    CollisionResult checkCircleRectangleCollision(
        const sf::Vector2f& circleCenter,
        float circleRadius,
        const sf::Vector2f& rectPos,
        const sf::Vector2f& rectSize
    );

    // Reflect a velocity vector based on a collision normal
    sf::Vector2f reflect(const sf::Vector2f& velocity, const sf::Vector2f& normal);
}