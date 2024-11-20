#pragma once

namespace Config
{
    constexpr size_t windowWidth = 1024;
    constexpr size_t windowHeight = 576;
    constexpr size_t frameRate = 144;

    constexpr float paddleWidth = 130.f;
    constexpr float paddleHeight = 15.f;
    constexpr float ballRadius = 15.f;

    constexpr float paddleOffset = 35.f;

    constexpr float paddleSpeed = windowWidth * 0.45f;
    constexpr float ballSpeed = windowHeight * 3.55f;

    constexpr float brickWidth = 100.f;
    constexpr float brickHeight = 35.f;
    constexpr float brickMargin = 8.f;

    constexpr float bricksLayoutCoverage = 0.55f;

    constexpr size_t bricksLayoutX = windowWidth / (brickWidth + brickMargin);
    constexpr size_t bricksLayoutY = windowHeight * bricksLayoutCoverage / (brickHeight + brickMargin);
    constexpr size_t bricksCount = bricksLayoutX * bricksLayoutY;

    constexpr float bricksLayoutOffsetX = (windowWidth - (brickWidth + brickMargin) * bricksLayoutX) * 0.5f;
    constexpr float bricksLayoutOffsetY = ballRadius * 1.25f;
}
