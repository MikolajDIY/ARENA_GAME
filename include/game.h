#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "textureMenager.h"
#include "player.h"
#include "shop.h"
#include "button.h"
#include "settings.h"
class Arena;

enum class GameState{MainMenu,Arena,Shop,GameOver, Settings, Intro};

class Game{
private:
    int window_width = 800;
    int window_height = 600;

    sf::RenderWindow window;
    TextureMenager textures;

    Player player;
    Shop shop;
    Settings settings;
    Arena* currentArena = nullptr;

    Button* btnStart = nullptr;
    Button* btnMenu = nullptr;
    Button* btnShop = nullptr;
    Button* btnSettings = nullptr;
    Button* btnExit = nullptr;

    bool isMouseClicked_Left = false;
    bool isMouseClicked_Right = false;

    // Intor
    sf::Sprite introSprite;
    sf::Clock introClock;
    int introStage = 1;
    bool isIntroInitialized = false;

public:
    int points;

    Game();
    ~Game();

    void Run();

    void DisplayMenu(sf::RenderWindow& window, GameState& Menu_State, sf::Vector2i& Mouse_pos);
    void DisplayArena(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, sf::Vector2i& Mouse_pos);
    void DisplaySettings(sf::RenderWindow& window, GameState& Menu_State, sf::Vector2i& Mouse_pos);
    void DisplayShop(sf::RenderWindow& window, GameState& Menu_State, sf::Vector2i& Mouse_pos);
    void DisplayIntro(sf::RenderWindow& window, GameState& Menu_State);
};
