#include "igra.h"
#include <algorithm>

Igra::Igra()
    : prozor(sf::VideoMode({ 800, 600 }), "Space Shooter"),
    bodovi(0), zivoti(6), krajIgre(false)
{
    prozor.setFramerateLimit(60);
    stvoriValNeprijatelja();
}

void Igra::stvoriValNeprijatelja()
{
    // Resetka 4x8 neprijatelja
    neprijatelji.clear();
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 8; c++)
            neprijatelji.emplace_back(sf::Vector2f(80.f + c * 80.f, 40.f + r * 60.f));
}

void Igra::resetirajIgru()
{
    bodovi = 0;
    zivoti = 6;
    krajIgre = false;
    metci.clear();
    eksplozije.clear();
    igrac.reset();
    stvoriValNeprijatelja();
}

void Igra::provjeriSudare()
{
    // 1. Metak vs Neprijatelj
    for (auto& b : metci)
    {
        for (auto& e : neprijatelji)
        {
            if (!b.alive || !e.alive) continue;

            auto br = b.getBounds();
            auto er = e.getBounds();

            // AABB kolizija - provjera preklapanja pravokutnika
            if (br.position.x < er.position.x + er.size.x &&
                br.position.x + br.size.x > er.position.x &&
                br.position.y < er.position.y + er.size.y &&
                br.position.y + br.size.y > er.position.y)
            {
                b.alive = false;  // Unisti metak
                e.alive = false;  // Unisti neprijatelja
                bodovi += 10;     // Bodovi
                eksplozije.emplace_back(e.getPosition());
            }
        }
    }
    // 2. Neprijatelj vs Igrac
    for (auto& e : neprijatelji)
    {
        if (!e.alive) continue;

        auto pr = igrac.getBounds();
        auto er = e.getBounds();
        // Kolizija igrac-neprijatelj
        if (pr.position.x < er.position.x + er.size.x &&
            pr.position.x + pr.size.x > er.position.x &&
            pr.position.y < er.position.y + er.size.y &&
            pr.position.y + pr.size.y > er.position.y)
        {
            e.alive = false;
            zivoti--;
        }
        // 3. Neprijatelj je prošao igraca
        if (e.getPosition().y > 600.f)
        {
            e.alive = false;
            zivoti--;
        }
    }

    if (zivoti <= 0)
        krajIgre = true; // Game over
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

        // AZURIRANJE STANJA
        igrac.update(dt);

        if (igrac.mozePucati()) // Kretanje igraca
            metci.push_back(igrac.pucaj()); // Dodaj novi metak

        for (auto& b : metci) b.update(dt);
        for (auto& e : neprijatelji) e.update(dt);
        for (auto& ex : eksplozije) ex.update(dt);

        provjeriSudare(); // Detektiraj kolizije

        metci.erase(std::remove_if(metci.begin(), metci.end(),
            [](auto& b) { return !b.alive; }), metci.end());

        neprijatelji.erase(std::remove_if(neprijatelji.begin(), neprijatelji.end(),
            [](auto& e) { return !e.alive; }), neprijatelji.end());

        eksplozije.erase(std::remove_if(eksplozije.begin(), eksplozije.end(),
            [](auto& e) { return e.finished; }), eksplozije.end());

        // Novi val ako su svi neprijatelji mrtvi
        if (neprijatelji.empty())
            stvoriValNeprijatelja();

        prikaz.update(bodovi, zivoti); // Azuriraj HUD

        prozor.clear();
        igrac.draw(prozor);
        for (auto& b : metci) b.draw(prozor);
        for (auto& e : neprijatelji) e.draw(prozor);
        for (auto& ex : eksplozije) ex.draw(prozor);
        prikaz.draw(prozor);
        prozor.display();
    }
}