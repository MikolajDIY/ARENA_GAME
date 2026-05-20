#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "textureMenager.h"
#include "utils.h"

class Button;
class Player;

class Settings{
private:
    sf::Sprite BackGround;
    std::map<std::string, Button*> buttons;
    std::map<std::string, sf::Text> texts;

public:
    Settings(TextureMenager& textures, Player& player);
    ~Settings();

    bool Update(Utils::Mouse& mouse);
    void Draw(sf::RenderWindow& window);
};
