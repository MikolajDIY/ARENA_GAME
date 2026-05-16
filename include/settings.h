#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "textureMenager.h"
class Button;
class Player;

class Settings{
private:
    std::map<std::string, Button*> buttons;
    std::map<std::string, sf::Text> texts;

public:
    Settings(TextureMenager& textures, Player& player);
    ~Settings();

    bool Update(int mouseX, int mouseY, bool isClicked);
    void Draw(sf::RenderWindow& window);
};
