#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextureMenager{
private:
    // Textury postaci i tla
    sf::Texture arenaBackGroundTexture;
    sf::Texture playerTexture;
    sf::Texture BossTexture;
    sf::Texture ZombieTexture;
    sf::Texture SkeletonTexture;
    sf::Texture MageTexture;

    // Czcionki
    sf::Font mainFont;

    // Textury itemow
    sf::Texture testSword;

public:
    TextureMenager();
    ~TextureMenager();
    friend class Arena;

    // Gettery
    sf::Font& getMainFont();

    sf::Texture& getPlayerTexture();
};
