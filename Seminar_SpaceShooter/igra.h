#pragma once
#include <SFML/Graphics.hpp>
#include "entiteti.h"
#include "headup.h"
#include <vector>
#include <optional>


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
    int trenutniVal = 1;

    // TEXTURE
    sf::Texture texIgrac;
    sf::Texture texMetak;
    sf::Texture texNeprijatelj;
    sf::Texture texEksplozija;




    void stvoriValNeprijatelja();
    void resetirajIgru();
    void provjeriSudare();

public:
    Igra();
    void pokreni();
};
