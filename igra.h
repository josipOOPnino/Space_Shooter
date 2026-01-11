#pragma once
#include <SFML/Graphics.hpp>
#include "entiteti.h"
#include "headup.h"
#include <vector>

class Igra
{
private:
    sf::RenderWindow prozor;
    sf::Clock sat;

    Igrac igrac;
    std::vector<Metak> metci;
    std::vector<Neprijatelj> neprijatelji;
    std::vector<Eksplozija> eksplozije;

    HUD prikaz;

    int bodovi;
    int zivoti;
    bool krajIgre;

    void stvoriValNeprijatelja();
    void resetirajIgru();
    void provjeriSudare();

public:
    Igra();
    void pokreni();
};