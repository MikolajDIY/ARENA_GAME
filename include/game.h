#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "textureMenager.h"
#include "player.h"
#include "shop.h"
#include "button.h"
#include "settings.h"
#include "utils.h"
class Arena;

enum class GameState{MainMenu,Arena,Shop,GameOver, Settings, Intro};

class Game{
private:
    int window_width = 800;
    int window_height = 600;

    sf::RenderWindow window;
    sf::Sprite menuBackGround;
    TextureMenager textures;

    Player player;
    Shop shop;
    Settings settings;
    Arena* currentArena = nullptr;

    std::map<std::string, Button*> buttons;

    Utils::Mouse mouse;

    // Intor
    sf::Sprite introSprite;
    sf::Clock introClock;
    int introStage = 0;

public:
    int points;

    Game();
    ~Game();

    void Run();

    void DisplayMenu(sf::RenderWindow& window, GameState& Menu_State, Utils::Mouse& mouse);
    void DisplayArena(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, Utils::Mouse& mouse);
    void DisplaySettings(sf::RenderWindow& window, GameState& Menu_State, Utils::Mouse& mouse);
    void DisplayShop(sf::RenderWindow& window, GameState& Menu_State, Utils::Mouse& mouse);
    void DisplayIntro(sf::RenderWindow& window, GameState& Menu_State);
};
