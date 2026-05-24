#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "textureMenager.h"
#include "item.h"

struct PlayerStats{
    int demage;
    int health;
};

struct PlayerDraw{
    sf::Sprite PlayerSprite;
    sf::Sprite SwordSprite;
    sf::Text HpBar;
    sf::Text Name;
};

class Player{
private:
    // Wyswietlanie gracza
    std::string name;

    // Zbior rzeczy skladajacych sie na wyswietlenie gracza
    PlayerDraw playerDraw;

    sf::Vector2f position;
    TextureMenager& textures;

    // Aktulany ekwipunek gracza
    SwordsTypes sword;
    ArmorsTypes armor;

    // Odblokowane przedmioty SKLEP I USTAWIENIA
    std::map<SwordsTypes, bool> unlockedSwords;
    std::map<ArmorsTypes, bool> unlockedArmors;
    int gold;
    int points;

    // Statystyki bitewne gracza
    PlayerStats stats;

public:
    Player(TextureMenager& textures);

    // SKLEP I USTAWIENIA - ekwipunek
    int getGold();

    void setSword(SwordsTypes newSword); // Te metody mog¹ tez zmieniac hp i demage gracza
    void setArmor(ArmorsTypes newArmor);

    bool hasSword(SwordsTypes sword) const;
    bool hasArmor(ArmorsTypes armor) const;

    void unlockSword(SwordsTypes sword);
    void unlockArmor(ArmorsTypes armor);

    bool buySword(SwordsTypes sword, int price);
    bool buyArmor(ArmorsTypes armor, int price);

    // Rysowanie Gracza
    void Update();
    void Update(float x, float y);
    void HpBarUpdate();
    void Draw(sf::RenderWindow& window);
};
