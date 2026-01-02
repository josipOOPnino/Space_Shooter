#include "HUD.h"

HUD::HUD()
    : font("assets/font.ttf"),
    scoreText(font)
{
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(10.f, 10.f));
}

void HUD::update(int score)
{
    scoreText.setString("Score: " + std::to_string(score));
}

void HUD::draw(sf::RenderWindow& window)
{
    window.draw(scoreText);
}
