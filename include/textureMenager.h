#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextureMenager{
private:
    // Textury postaci i tla
    sf::Texture arenaBackGroundTexture;

    sf::Texture playerTextureBasic;
    sf::Texture playerTextureSteel;
    sf::Texture playerTextureGodnes;

    sf::Texture BossTexture;
    sf::Texture ZombieTexture;
    sf::Texture SkeletonTexture;
    sf::Texture MageTexture;

    // Czcionki
    sf::Font mainFont;

    // Textury itemow
    sf::Texture basicSwordTexture;
    sf::Texture steelSwordTexture;
    sf::Texture godnesSwordTexture;

public:
    TextureMenager();
    ~TextureMenager();
    friend class Arena;

    // Gettery
    sf::Font& getMainFont();

    sf::Texture& getPlayerTextureBasic();
    sf::Texture& getBasicSwordTexture();

    sf::Texture& getPlayerTextureSteel();
    sf::Texture& getSteelSwordTexture();

    sf::Texture& getPlayerTextureGodnes();
    sf::Texture& getGodnesSwordTexture();
};
