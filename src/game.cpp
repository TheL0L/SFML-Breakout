#include "game.h"
#include "collision.h"
#include <cmath>

float getRandomValue(std::mt19937& randomEngine, float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(randomEngine);
}


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
    
    auto const angle = getRandomValue(randomEngine, 20, 160);
    ballVelocity.x = Config::ballSpeed * std::sin(angle);
    ballVelocity.y = Config::ballSpeed * std::cos(angle);
}

void Game::initBricksLayout()
{
    auto const brickSize = sf::Vector2f(
        Config::brickWidth + Config::brickMargin,
        Config::brickHeight + Config::brickMargin
    );
    auto position = sf::Vector2f();
    sf::Color color;

    for (size_t row = 0; row < Config::bricksLayoutY; ++row)
    {
        color = sf::Color(
            getRandomValue(randomEngine, 0, 100),
            getRandomValue(randomEngine, 10, 255),
            getRandomValue(randomEngine, 10, 255)
        );

        for (size_t col = 0; col < Config::bricksLayoutX; ++col)
        {
            position = sf::Vector2f(
                col * brickSize.x + Config::bricksLayoutOffsetX,
                row * brickSize.y + Config::bricksLayoutOffsetY
            );
            bricks.emplace_back(position, row, color);
        }
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

    if (bricks.size() == 0)
    {  // game won
        ball.setFillColor(sf::Color::Green);

        initBricksLayout();
    }
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

void Game::checkCollisions()
{
    sf::Vector2f ballCenter = ball.getPosition() + sf::Vector2f(ball.getRadius(), ball.getRadius());

    CollisionResult paddleCollision = Collision::checkCircleRectangleCollision(
        ballCenter,
        ball.getRadius(),
        paddle.getPosition(),
        paddle.getSize());

    if (paddleCollision.collided)
    {
        ballVelocity = Collision::reflect(ballVelocity, paddleCollision.normal);
        ball.setPosition(ball.getPosition() + paddleCollision.normal * paddleCollision.penetration);
    }

    for (auto& brick : bricks)
    {
        if (brick.isActive())
        {
            CollisionResult brickCollision = Collision::checkCircleRectangleCollision(
                ballCenter,
                ball.getRadius(),
                brick.getPosition(),
                brick.getSize()
            );

            if (brickCollision.collided)
            {
                ballVelocity = Collision::reflect(ballVelocity, brickCollision.normal);
                ball.setPosition(ball.getPosition() + brickCollision.normal * brickCollision.penetration);
                brick.takeHit(1);
                break;
            }
        }
    }
}

void Game::removeDestroyedBricks()
{
    bricks.erase(
        std::remove_if(bricks.begin(), bricks.end(),
            [](const Brick& brick) { return !brick.isActive(); }
        ),
        bricks.end()
    );
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
