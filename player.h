#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "textureMenager.h"

class Player{
private:
    std::string name;
    sf::Sprite playerSprite;
    sf::Sprite swordSprite;
public:
    Player(TextureMenager& textures);

    void Draw(sf::RenderWindow& window);
};
