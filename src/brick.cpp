#include "brick.h"

const sf::Color interpolateColor(sf::Color A, sf::Color B, float t)
{
    float r = (1 - t) * A.r + t * B.r;
    float g = (1 - t) * A.g + t * B.g;
    float b = (1 - t) * A.b + t * B.b;
    float a = (1 - t) * A.a + t * B.a;
    
    return sf::Color(r, g, b, a);
}


Brick::Brick(sf::Vector2f position, size_t health, sf::Color color) : health(health), maxHealth(health),
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
    if (damage >= health) damage = health;

    health -= damage;
    shape.setFillColor(interpolateColor(shape.getFillColor(), sf::Color::Red, (maxHealth - health) / (float)maxHealth));
}

bool Brick::isActive() const
{
    return (health > 0);
}
