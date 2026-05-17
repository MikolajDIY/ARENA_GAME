#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "textureMenager.h"
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

    bool Update(int mouseX, int mouseY, bool isClicked);
    void Draw(sf::RenderWindow& window);
};

