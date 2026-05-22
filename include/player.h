#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "textureMenager.h"
#include "item.h"

class Player{
private:
    // Wyswietlanie gracza
    std::string name;
    sf::Sprite playerSprite;
    sf::Sprite swordSprite;
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
    void Draw(sf::RenderWindow& window);
};
