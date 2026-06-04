#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include "game.h"
#include "enemy.h"
inline sf::Font font;

enum class TurnState{PlayerMove, PlayerAttack, EnemiesTurn, GameOver};

class Arena{
private:
    std::string name;
    sf::Sprite arenaBackGround;
    Utils::Menagers& menagers;
    TurnState currentState;
    Player& player;

    std::vector<Enemy*> enemies;
    int currentTurn;
    int maxTurns;

    Button* btnBackToMenu = nullptr;
    Button* btnAttackBasic = nullptr;
    Button* btnAttackReckless = nullptr;
    Button* btnAttackRisky = nullptr;
    Button* btnAttackCombo = nullptr;
    Button* btnHeal = nullptr;

    Enemy* selectedEnemy = nullptr;
    bool isPlayerSelected = false;

    MessageMenager* msgManager = nullptr;
    sf::Clock turnDelayClock;

    void HandleTargetSelection(const sf::Vector2f& mouseCoord);
    void HandlePlayerAttacks(Utils::Mouse& Mouse);
    void ExecuteAttack(AttackType attackType);
    void HandleEnemyDefeat();
    bool CheckGameOverConditions();
    void SpawnEnemies();

public:
    Arena(std::string arenaName, Utils::Menagers& menagers, Player& mainPlayer);

    ~Arena();

    void Fight();

    bool Update(Utils::Mouse& Mouse);

    void Draw(sf::RenderWindow& window);

};
