#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "textureMenager.h"
enum class SwordsTypes{Basic, Steel, Godnes};
enum class PlayerType{Basic, Steel, Godnes};

class Player{
private:
    // Wyswietlanie gracza
    std::string name;
    sf::Sprite playerSprite;
    sf::Sprite swordSprite;
    sf::Vector2f position;
    TextureMenager& textures;

    // Czym aktualnie jest gracz
    SwordsTypes swordtype;
    PlayerType playertype;

    // Odblokowane przedmioty SKLEP I USTAWIENIA
    std::map<SwordsTypes, bool> unlockedSwords;
    std::map<PlayerType, bool> unlockedSkins;
    unsigned int gold;
    unsigned int points;

public:
    Player(TextureMenager& textures);

    // SKLEP I USTAWIENIA - ekwipunek
    void setSword(SwordsTypes sword);
    void setArmor(PlayerType armor);

    // Rysowanie Gracza
    void Update();
    void Update(float x, float y);
    void Draw(sf::RenderWindow& window);
};
