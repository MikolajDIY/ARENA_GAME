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
    Utils::Mouse& mouse;

    Player& player;

public:
    Shop(TextureMenager& textures, Player& player, Utils::Mouse& mouse);
    ~Shop();

    bool Update(Utils::Mouse& mouse);
    void Draw(sf::RenderWindow& window);
};

