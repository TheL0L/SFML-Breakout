#include "game.h"

Game::Game() : window(sf::VideoMode(Config::windowWidth, Config::windowHeight), "Breakout")
{
    initWindow();
    initGameObjects();
}

Game::~Game() {}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::initWindow()
{
    window.setFramerateLimit(Config::frameRate);
}

void Game::initGameObjects()
{
    paddle.setSize(sf::Vector2f(Config::paddleWidth, Config::paddleHeight));
    paddle.setPosition(
        window.getSize().x / 2 - paddle.getSize().x / 2,
        window.getSize().y - paddle.getSize().y - Config::paddleOffset
    );
    paddle.setFillColor(sf::Color::White);

    ball.setRadius(Config::ballRadius);
    ball.setPosition(
        paddle.getPosition().x + paddle.getSize().x / 2 - ball.getRadius(),
        paddle.getPosition().y - paddle.getSize().y / 2 - ball.getRadius() * 2
    );
    ball.setFillColor(sf::Color::White);
    
    initBricksLayout();
}

void Game::initBricksLayout()
{
    auto health = Config::bricksLayoutY;
    auto const brickSize = sf::Vector2f(
        Config::brickWidth + Config::brickMargin,
        Config::brickHeight + Config::brickMargin
    );
    auto position = sf::Vector2f();
    auto color = sf::Color::Red;

    for (size_t row = 0; row < Config::bricksLayoutY; ++row)
    {
        for (size_t col = 0; col < Config::bricksLayoutX; ++col)
        {
            position = sf::Vector2f(
                col * brickSize.x + Config::bricksLayoutOffsetX,
                row * brickSize.y + Config::bricksLayoutOffsetY
            );
            bricks.emplace_back(position, health, color);
        }
        --health;
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();
    }
}

void Game::update()
{

}

void Game::render()
{
    window.clear(sf::Color::Black);

    for (const auto& brick : bricks)
        brick.draw(window);

    window.draw(paddle);
    window.draw(ball);

    window.display();
}
