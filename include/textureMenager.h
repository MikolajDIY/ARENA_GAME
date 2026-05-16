#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextureMenager{
private:
    // Textury tla
    sf::Texture arenaBackGround;
    sf::Texture menuBackGround;
    sf::Texture studio;
    sf::Texture gameName;

    // Textury Gracza
    sf::Texture playerTextureBasic;
    sf::Texture playerTextureSteel;
    sf::Texture playerTextureGodnes;

    // Textury Przeciwnikow
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
    // TLA
    sf::Texture& getStudio();
    sf::Texture& getGameName();
    sf::Texture& getMenuBackGround();
    sf::Texture& getArenaBackGround();

    // GRACZ I JEGO EKWIPUNEK
    sf::Texture& getPlayerTextureBasic();
    sf::Texture& getBasicSwordTexture();

    sf::Texture& getPlayerTextureSteel();
    sf::Texture& getSteelSwordTexture();

    sf::Texture& getPlayerTextureGodnes();
    sf::Texture& getGodnesSwordTexture();

    // PRZECIWNICY
    sf::Texture& getSkeleton();
    sf::Texture& getZombie();
    sf::Texture& getMage();
    sf::Texture& getBoss();
};
