#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "game.h"
#include "enemy.h"
inline sf::Font font;

enum class TurnState{PlayerMove, PlayerAttack, EnemiesTurn};

class Arena{
private:
    std::string name;
    sf::Sprite arenaBackGround;
    TextureMenager& textures;
    TurnState currentState;
    Player& player;

    std::vector<Enemy*> enemies;

    Button* btnBackToMenu = nullptr;

public:
    Arena(std::string arenaName, TextureMenager& textures, Player& mainPlayer);

    ~Arena();

    void Fight();

    bool Update(int mouseX, int mouseY, bool isClicked);

    void Draw(sf::RenderWindow& window);

};
