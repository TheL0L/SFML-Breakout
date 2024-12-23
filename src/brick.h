#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"

class Brick
{
public:
    Brick(sf::Vector2f position, size_t health, sf::Color color);
    ~Brick();

    void draw(sf::RenderWindow& renderer) const;
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    void takeHit(size_t damage);
    bool isActive() const;

private:
    size_t maxHealth;
    size_t health;
    sf::RectangleShape shape;
};
