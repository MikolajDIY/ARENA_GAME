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

class Player;
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

    int gold; // ile zlota daje jego smierc
    int points; // ile punktow daje jego smierc
    bool isDeath; // tego nie uzywam ale moze sie wam przyda...

public:
    Enemy(TextureMenager& textures);
    virtual ~Enemy(){};

    Enemy& operator*=(float multiplier);

    int getGold() const { return gold; }
    int getPoints() const { return points; }
    const sf::Sprite& getSprite() const { return enemyDraw.EnemySprite; }
    bool isDead() const { return stats.health <= 0; }
    int getHealth() const { return stats.health; }
    EnemyTypes getType() const { return type; }

    // Metody walki
    void TakeDamage(int amount);
    virtual void Attack(Player& target)=0;

    // Rysowanie Przeciwnika
    void Update();
    void Update(float x, float y);
    virtual void HpBarUpdate();
    virtual void Draw(sf::RenderWindow& window);
};
