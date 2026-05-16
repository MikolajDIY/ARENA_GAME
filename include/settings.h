#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "textureMenager.h"
class Button;
class Player;

class Settings{
private:
    Button* btnBackToMenu;

public:
    Settings(TextureMenager& textures, Player& player);
    ~Settings();

    bool Update(int mouseX, int mouseY, bool isClicked);
    void Draw(sf::RenderWindow& window);
};
