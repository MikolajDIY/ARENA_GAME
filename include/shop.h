#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "textureMenager.h"
#include "utils.h"
class Button;
class Player;

class Shop{
private:
    sf::Sprite BackGround;
    std::map<std::string, Button*> buttons;
    std::map<std::string, sf::Text> texts;

    Player& player;

public:
    Shop(TextureMenager& textures, Player& player);
    ~Shop();

    bool Update(Utils::Mouse& mouse);
    void Draw(sf::RenderWindow& window);
};

