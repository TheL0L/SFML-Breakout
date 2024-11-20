#include "game.h"

Game::Game() : window(sf::VideoMode(Config::windowWidth, Config::windowHeight), "Breakout")
{
    initWindow();
    initGameObjects();
}

Game::~Game() {}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
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

void Game::update(float deltaTime)
{
    updatePaddle(deltaTime);
    updateBall(deltaTime);

    checkCollisions();
    removeDestroyedBricks();
}

void Game::updatePaddle(float deltaTime)
{
    bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    if (leftPressed && rightPressed) paddleVelocity.x = 0;
    else if (leftPressed) paddleVelocity.x = -Config::paddleSpeed;
    else if (rightPressed) paddleVelocity.x = Config::paddleSpeed;
    else paddleVelocity.x = 0;

    paddle.move(paddleVelocity * deltaTime);

    paddle.setPosition(ball.getPosition().x + ball.getRadius() - Config::paddleWidth * 0.5f, paddle.getPosition().y);

    if (paddle.getPosition().x < 0.f)
        paddle.setPosition(0.f, paddle.getPosition().y);
    if (paddle.getPosition().x + paddle.getSize().x > window.getSize().x)
        paddle.setPosition(window.getSize().x - paddle.getSize().x, paddle.getPosition().y);
}

void Game::updateBall(float deltaTime)
{
    ball.move(ballVelocity * deltaTime);

    if (ball.getPosition().x < 0.f)
        ballVelocity.x = abs(ballVelocity.x);
    if (ball.getPosition().x + ball.getRadius() * 2 > window.getSize().x)
        ballVelocity.x = -abs(ballVelocity.x);
    if (ball.getPosition().y < 0.f)
        ballVelocity.y = abs(ballVelocity.y);
    
    if (ball.getPosition().y > window.getSize().y - ball.getRadius() * 2)
    {  // game over
        ballVelocity.y = -abs(ballVelocity.y);
        ball.setFillColor(sf::Color::Red);
    }
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
