#include "brick.h"


Brick::Brick(sf::Vector2f position, size_t health, sf::Color color) : health(health),
    shape(sf::RectangleShape(sf::Vector2f(Config::brickWidth, Config::brickHeight)))
{
    auto const offset = sf::Vector2f(Config::brickMargin, Config::brickMargin);
    shape.setPosition(position + offset);
    shape.setFillColor(color);
}

Brick::~Brick() {}

void Brick::draw(sf::RenderWindow& renderer) const
{
    renderer.draw(shape);
}

sf::FloatRect Brick::getBoundingBox() const
{
    return shape.getGlobalBounds();
}

void Brick::takeHit(size_t damage)
{
    health = (damage >= health) ? 0 : health - damage;
}

bool Brick::isActive() const
{
    return (health > 0);
}
