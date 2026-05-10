#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "game.h"
inline sf::Font font;

enum class TurnState{PlayerMove, PlayerAttack, EnemiesTurn};

class Arena{
private:
    std::string name;
    sf::Texture backgroundTexture;
    std::vector<sf::Texture> enemyTextures;
    sf::Sprite backgroundSprite;
    sf::Font arenaFont;
    TurnState currentState;
    // std::vector<Enemy*> enemies; // Po napisaniu klasy Enemy odkomentowac

    Button* btnBackToMenu = nullptr;

public:
    Arena(std::string arenaName, sf::Font font);

    ~Arena();

    void Fight();

    bool Update(int mouseX, int mouseY, bool isClicked);

    void Draw(sf::RenderWindow& window);

};
