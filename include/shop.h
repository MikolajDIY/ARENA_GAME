#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "textureMenager.h"
class Button;
class Player;

class Shop{
private:
    Button* btnBackToMenu;

public:
    Shop(TextureMenager& textures, Player& player);
    ~Shop();

    bool Update(int mouseX, int mouseY, bool isClicked);
    void Draw(sf::RenderWindow& window);
};

