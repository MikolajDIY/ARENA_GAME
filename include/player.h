#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "textureMenager.h"
enum class SwordsTypes{SteelSword, GoldSword, WoodenSword};

class Player{
private:
    std::string name;
    sf::Sprite playerSprite;
    sf::Sprite swordSprite;
    sf::Vector2f position;
    SwordsTypes swordtype;

public:
    Player(TextureMenager& textures);

    void Update();
    void Draw(sf::RenderWindow& window);
};
