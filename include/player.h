#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "textureMenager.h"
enum class SwordsTypes{Basic, Steel, Godnes};
enum class PlayerType{Basic, Steel, Godnes};

class Player{
private:
    std::string name;
    sf::Sprite playerSprite;
    sf::Sprite swordSprite;
    sf::Vector2f position;
    TextureMenager& textures;

    // Czym aktualnie jest gracz
    SwordsTypes swordtype;
    PlayerType playertype;

    // Odblokowane przedmioty
    std::map<SwordsTypes, bool> unlockedSwords;
    std::map<PlayerType, bool> unlockedSkins;

public:
    Player(TextureMenager& textures);

    void Update();
    void Draw(sf::RenderWindow& window);
};
