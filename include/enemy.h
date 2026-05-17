#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "textureMenager.h"

class Enemy{
protected:
    // Wyswietlanie gracza
    std::string name;
    sf::Sprite enemySprite;
    sf::Vector2f position;
    TextureMenager& textures;

    unsigned int gold; // ile zlota daje jego smierc
    unsigned int points; // ile punktow daje jego smierc
    bool isDeath;

public:
    Enemy(TextureMenager& textures);
    virtual ~Enemy(){};

    // Rysowanie Przeciwnika
    void Update();
    void Update(float x, float y);
    void Draw(sf::RenderWindow& window);
};
