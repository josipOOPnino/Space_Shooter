#include "igra.h"
#include <algorithm>
#include <iostream>


Igra::Igra()
    : prozor(sf::VideoMode({ 800, 600 }), "Space Shooter"),
    bodovi(0),
    zivoti(6),
    krajIgre(false)
{
    prozor.setFramerateLimit(60);
    trenutniVal = 1;

    if (!texIgrac.loadFromFile("assets/sprites/igrac.png"))
        std::cout << "NE UCITAVA igrac.png\n";

    if (!texMetak.loadFromFile("assets/sprites/metak.png"))
        std::cout << "NE UCITAVA metak.png\n";

    if (!texNeprijatelj.loadFromFile("assets/sprites/neprijatelj.png"))
        std::cout << "NE UCITAVA neprijatelj.png\n";

    if (!texEksplozija.loadFromFile("assets/sprites/eksplozija.png"))
        std::cout << "NE UCITAVA eksplozija.png\n";


    igrac.init(texIgrac);

    stvoriValNeprijatelja();
}

void Igra::stvoriValNeprijatelja()
{
    neprijatelji.clear();

    ValTip tip = (trenutniVal == 1) ? ValTip::Val1
        : (trenutniVal == 2) ? ValTip::Val2
        : ValTip::Val3;

    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            neprijatelji.emplace_back(
                sf::Vector2f(80.f + c * 80.f, 80.f + r * 60.f),
                tip,
                texNeprijatelj
            );
        }
    }
}

void Igra::resetirajIgru()
{
    bodovi = 0;
    zivoti = 6;
    krajIgre = false;
    trenutniVal = 1;

    metci.clear();
    eksplozije.clear();

    igrac.reset();
    stvoriValNeprijatelja();
}

void Igra::provjeriSudare()
{
    for (auto& b : metci)
    {
        for (auto& e : neprijatelji)
        {
            if (!b.alive || !e.alive) continue;

            if (b.getBounds().findIntersection(e.getBounds()))
            {
                b.alive = false;
                e.alive = false;
                bodovi += 10;

                eksplozije.emplace_back(e.getPosition(), texEksplozija);
            }
        }
    }
    for (auto& e : neprijatelji)
    {
        if (!e.alive) continue;

        if (igrac.getBounds().findIntersection(e.getBounds()))
        {
            e.alive = false;
            zivoti--;
        }

        if (e.getPosition().y > 600.f)
        {
            e.alive = false;
            zivoti--;
        }
    }

    if (zivoti <= 0)
        krajIgre = true;
}

void Igra::pokreni()
{
    while (prozor.isOpen())
    {
        float dt = sat.restart().asSeconds();

        while (auto e = prozor.pollEvent())
            if (e->is<sf::Event::Closed>())
                prozor.close();

        if (krajIgre)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
                resetirajIgru();

            prozor.clear();
            prikaz.drawGameOver(prozor);
            prozor.display();
            continue;
        }

        igrac.update(dt);

        if (igrac.mozePucati())
            metci.push_back(igrac.pucaj(texMetak));

        for (auto& b : metci) b.update(dt);
        for (auto& e : neprijatelji) e.update(dt);
        for (auto& ex : eksplozije) ex.update(dt);

        provjeriSudare();

        metci.erase(std::remove_if(metci.begin(), metci.end(),
            [](auto& b) { return !b.alive; }), metci.end());

        neprijatelji.erase(std::remove_if(neprijatelji.begin(), neprijatelji.end(),
            [](auto& e) { return !e.alive; }), neprijatelji.end());

        eksplozije.erase(std::remove_if(eksplozije.begin(), eksplozije.end(),
            [](auto& e) { return e.finished; }), eksplozije.end());

        if (neprijatelji.empty())
        {
            trenutniVal++;
            if (trenutniVal > 3)
                trenutniVal = 1;

            stvoriValNeprijatelja();
        }

        prikaz.update(bodovi, zivoti);

        prozor.clear();

        igrac.draw(prozor);
        for (auto& b : metci) b.draw(prozor);
        for (auto& e : neprijatelji) e.draw(prozor);
        for (auto& ex : eksplozije) ex.draw(prozor);

        prikaz.draw(prozor);
        prozor.display();
    }
}
