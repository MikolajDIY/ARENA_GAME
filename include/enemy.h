#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "textureMenager.h"

struct EnemyDraw{
    sf::Sprite EnemySprite;
    sf::Text HpBar;
    sf::Text Name;
    sf::Text Name2;
};

struct EnemyStats{
    int health;
    int damage;
};

enum class EnemyTypes{Skeleton, Zombie, Mage, Boss};

class Enemy{
protected:
    // Wyswietlanie Enemy
    std::string name;
    EnemyDraw enemyDraw;
    sf::Vector2f position;
    TextureMenager& textures;

    // Staty
    EnemyStats stats;
    EnemyTypes type;

    unsigned int gold; // ile zlota daje jego smierc
    unsigned int points; // ile punktow daje jego smierc
    bool isDeath; // tego nie uzywam ale moze sie wam przyda...

public:
    Enemy(TextureMenager& textures);
    virtual ~Enemy(){};

    // Rysowanie Przeciwnika
    void Update();
    void Update(float x, float y);
    virtual void HpBarUpdate();
    virtual void Draw(sf::RenderWindow& window);
};
