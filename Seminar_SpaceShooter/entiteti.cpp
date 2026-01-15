#include "entiteti.h"
#include <cmath>

static constexpr int ENEMY_W = 128;
static constexpr int ENEMY_H = 128;
static constexpr int ENEMY_FRAMES = 4;

static constexpr int EXP_W = 128;
static constexpr int EXP_H = 128;
static constexpr int EXP_FRAMES = 6;

static inline sf::IntRect RectPS(int x, int y, int w, int h)
{
    return sf::IntRect(sf::Vector2i(x, y), sf::Vector2i(w, h));
}

Metak::Metak(sf::Vector2f pos, const sf::Texture& tex)
    : sprite(tex)
{
    sprite.setOrigin(sf::Vector2f(
        tex.getSize().x / 1.f,
        tex.getSize().y / 1.f
    ));

    sprite.setPosition(pos);

    // laser look (duži po Y)
    sprite.setScale(sf::Vector2f(0.5f, 0.8f));

    velocity = sf::Vector2f(0.f, -800.f);
}

void Metak::update(float dt)
{
    sprite.move(velocity * dt);

    if (sprite.getPosition().y < -50.f)
        alive = false;
}

void Metak::draw(sf::RenderWindow& w) const { w.draw(sprite); }
sf::FloatRect Metak::getBounds() const { return sprite.getGlobalBounds(); }

Neprijatelj::Neprijatelj(sf::Vector2f pos, ValTip v, const sf::Texture& tex)
    : sprite(tex)
{
    val = v;

    sprite.setTextureRect(RectPS(0, 0, ENEMY_W, ENEMY_H));
    sprite.setOrigin(sf::Vector2f(ENEMY_W / 2.f, ENEMY_H / 2.f));
    sprite.setPosition(pos);

    // poveæaj na ekranu (po želji promijeni)
    sprite.setScale(sf::Vector2f(0.4f, 0.4f));

    if (val == ValTip::Val3)
        dirX = (pos.x < 400.f) ? -1.f : 1.f;
}

void Neprijatelj::update(float dt)
{
    vrijeme += dt;

    if (val == ValTip::Val1)
    {
        float x = dirX * 90.f * dt;
        float y = std::sin(vrijeme * 3.f) * 35.f * dt + 18.f * dt;

        sprite.move(sf::Vector2f(x, y));

        if (sprite.getPosition().x < 20.f || sprite.getPosition().x > 780.f)
            dirX *= -1.f;
    }
    else if (val == ValTip::Val2)
    {
        sprite.move(sf::Vector2f(dirX * 90.f * dt, 40.f * dt));

        if (sprite.getPosition().x < 20.f || sprite.getPosition().x > 780.f)
            dirX *= -1.f;
    }
    else // Val3
    {
        sprite.move(sf::Vector2f(dirX * 140.f * dt, 40.f * dt));

        if (sprite.getPosition().x < 20.f)  dirX = 1.f;
        if (sprite.getPosition().x > 780.f) dirX = -1.f;
    }

    // animacija
    frameTimer += dt;
    if (frameTimer >= 0.12f)
    {
        frame = (frame + 1) % ENEMY_FRAMES;
        frameTimer = 0.f;

        sprite.setTextureRect(RectPS(frame * ENEMY_W, 0, ENEMY_W, ENEMY_H));
    }
}

void Neprijatelj::draw(sf::RenderWindow& w) const { w.draw(sprite); }
sf::FloatRect Neprijatelj::getBounds() const { return sprite.getGlobalBounds(); }
sf::Vector2f Neprijatelj::getPosition() const { return sprite.getPosition(); }

Eksplozija::Eksplozija(sf::Vector2f pos, const sf::Texture& tex)
    : sprite(tex)
{
    sprite.setTextureRect(RectPS(0, 0, EXP_W, EXP_H));
    sprite.setOrigin(sf::Vector2f(EXP_W / 2.f, EXP_H / 2.f));
    sprite.setPosition(pos);

    // jaèe, retro
    sprite.setScale(sf::Vector2f(0.6f, 0.6f));
}

void Eksplozija::update(float dt)
{
    frameTimer += dt;

    if (frameTimer >= 0.06f)
    {
        frame++;
        frameTimer = 0.f;

        if (frame >= EXP_FRAMES)
        {
            finished = true;
            return;
        }

        sprite.setTextureRect(RectPS(frame * EXP_W, 0, EXP_W, EXP_H));
    }
}

void Eksplozija::draw(sf::RenderWindow& w) const { w.draw(sprite); }

void Igrac::init(const sf::Texture& tex)
{
    sprite.emplace(tex);

    sprite->setOrigin(sf::Vector2f(
        tex.getSize().x / 2.f,
        tex.getSize().y / 2.f
    ));

    sprite->setPosition(sf::Vector2f(400.f, 550.f));

    sprite->setScale({ 0.18f, 0.18f });


    timerPucanja = 0.f;
    brzina = 400.f;
}

void Igrac::reset()
{
    if (!sprite) return;

    sprite->setPosition(sf::Vector2f(400.f, 550.f));
    timerPucanja = 0.f;
}

void Igrac::update(float dt)
{
    if (!sprite) return;

    timerPucanja += dt;

    float pomak = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        pomak -= brzina * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        pomak += brzina * dt;

    sprite->move(sf::Vector2f(pomak, 0.f));

    float halfW = sprite->getGlobalBounds().size.x / 2.f;
    sf::Vector2f p = sprite->getPosition();

    if (p.x < halfW) p.x = halfW;
    if (p.x > 800.f - halfW) p.x = 800.f - halfW;

    sprite->setPosition(p);
}

bool Igrac::mozePucati() const
{
    return sprite
        && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)
        && timerPucanja > 0.20f;
}

Metak Igrac::pucaj(const sf::Texture& texMetak)
{
    timerPucanja = 0.f;

    sf::Vector2f p = sprite->getPosition();
    return Metak(sf::Vector2f(p.x, p.y - 40.f), texMetak);
}

void Igrac::draw(sf::RenderWindow& prozor) const
{
    if (sprite) prozor.draw(*sprite);
}

sf::FloatRect Igrac::getBounds() const
{
    if (!sprite) return sf::FloatRect();
    return sprite->getGlobalBounds();
}
