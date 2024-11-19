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
    
    window.draw(paddle);
    window.draw(ball);

    window.display();
}
