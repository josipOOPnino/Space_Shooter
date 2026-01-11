#include "headup.h"

HUD::HUD() : tekst(font), tekstKraja(font)
{
    font.openFromFile("assets/font.ttf");

    tekst.setCharacterSize(18);
    tekst.setPosition({ 10,10 });

    tekstKraja.setCharacterSize(32);
    tekstKraja.setPosition({ 220,260 });
    tekstKraja.setString("KRAJ IGRE\nPritisni R");
}

void HUD::update(int bodovi, int zivoti)
{
    tekst.setString("Bodovi: " + std::to_string(bodovi) + "  Zivoti: " + std::to_string(zivoti));
}

void HUD::draw(sf::RenderWindow& w) { w.draw(tekst); }
void HUD::drawGameOver(sf::RenderWindow& w) { w.draw(tekstKraja); }