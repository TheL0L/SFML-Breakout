#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
#include <vector>
#include "brick.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void initWindow();
    void initGameObjects();
    void initBricksLayout();

    void processEvents();
    void update(float deltaTime);
    void render();

    void updatePaddle(float deltaTime);
    void updateBall(float deltaTime);

    sf::RenderWindow window;

    sf::RectangleShape paddle;
    sf::CircleShape ball;

    sf::Vector2f paddleVelocity;
    sf::Vector2f ballVelocity;
    
    std::vector<Brick> bricks;
};
