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
    void update();
    void render();

    sf::RenderWindow window;

    sf::RectangleShape paddle;
    sf::CircleShape ball;
    
    std::vector<Brick> bricks;
};
