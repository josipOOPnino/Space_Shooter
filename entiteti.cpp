#include "entiteti.h"

Metak::Metak(sf::Vector2f pos)
{
    shape.setSize({ 4,12 });           // Mali pravokutnik
    shape.setPosition(pos);            // Pozicija igraca
    velocity = { 0,-600 };             // Krece se ravno prema gore
}

void Metak::update(float dt)
{
    shape.move(velocity * dt);         
    if (shape.getPosition().y < 0)     // Izasao iz ekrana
        alive = false;                 // Oznaci za brisanje
}

void Metak::draw(sf::RenderWindow& w) { w.draw(shape); }
sf::FloatRect Metak::getBounds() const { return shape.getGlobalBounds(); }

Neprijatelj::Neprijatelj(sf::Vector2f pos)
{
    shape.setSize({ 30,20 });          
    shape.setPosition(pos);            // Pozicija u resetci
}

// Neprijatelj se kreæe lijevo desno i prema dolje
void Neprijatelj::update(float dt)
{

    shape.move({ dir * 80.f * dt, 40.f * dt });

    // Odbijanje od rubova
    if (shape.getPosition().x < 20 || shape.getPosition().x > 750)
        dir *= -1.f;  
}

void Neprijatelj::draw(sf::RenderWindow& w) { w.draw(shape); }
sf::FloatRect Neprijatelj::getBounds() const { return shape.getGlobalBounds(); }
sf::Vector2f Neprijatelj::getPosition() const { return shape.getPosition(); }

Eksplozija::Eksplozija(sf::Vector2f pos)
{
    shape.setRadius(12);               // Pocetna velicina
    shape.setPosition(pos);            // Pozicija neprijatelja
}

void Eksplozija::update(float dt)
{
    timer += dt;                       // Vrijeme trajanja
    shape.setScale({ 1 + timer * 2, 1 + timer * 2 }); // Siri se
    if (timer > 0.3f)                  // Nakon 0.3 sekunde
        finished = true;               // Zavrsi efekt
}

void Eksplozija::draw(sf::RenderWindow& w) { w.draw(shape); }

Igrac::Igrac()
{
    oblik.setSize({ 40.f, 20.f });     // Brod igraca
    oblik.setPosition({ 380.f, 550.f }); // Centar dolje
    oblik.setFillColor(sf::Color::Green);

    timerPucanja = 0.f;                // Cooldown za pucanje
    brzina = 400.f;                    // Piksela po sekundi
}

void Igrac::reset()
{
    oblik.setPosition({ 380.f, 550.f }); // Vrati na pocetak
    timerPucanja = 0.f;                  // Reset cooldown
}

//upravljanje igracem
void Igrac::update(float dt)
{
    timerPucanja += dt;                // Cooldown timer

    float pomak = 0.f;

    // ULAZ S TIPKOVNICE - lijevo/desno
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        pomak -= brzina * dt;         
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        pomak += brzina * dt;
    }

    oblik.move({ pomak, 0.f });        

    // OGRANICENJE KRETANJA - ne izlazi iz ekrana
    if (oblik.getPosition().x < 0.f)
        oblik.setPosition({ 0.f, oblik.getPosition().y });

    if (oblik.getPosition().x + oblik.getSize().x > 800.f)
        oblik.setPosition({ 800.f - oblik.getSize().x, oblik.getPosition().y });
}

bool Igrac::mozePucati() const
{
    // Space + cooldown od 0.25 sekundi = rate limiting
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)
        && timerPucanja > 0.25f;
}

// STVARANJE NOVOG METKA
Metak Igrac::pucaj()
{
    timerPucanja = 0.f;     

    // Metak izlazi iz sredine broda 
    return Metak({
        oblik.getPosition().x + oblik.getSize().x / 2.f - 2.f, 
        oblik.getPosition().y                                  
        });
}

void Igrac::draw(sf::RenderWindow& prozor)
{
    prozor.draw(oblik);                
}

sf::FloatRect Igrac::getBounds() const
{
    return oblik.getGlobalBounds();    // Vrati za kolizije
}