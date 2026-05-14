#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "textureMenager.h"
#include "player.h"

class Arena;

enum class GameState{MainMenu,Arena,Shop,GameOver, Settings};

class Button{
private:
    sf::RectangleShape shape;
    sf::Text buttonText;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Vector2f Position;
    int fontSize;

public:
    Button(std::string text, sf::Vector2f pos, sf::Font& font, sf::Color normalC, sf::Color hoverC);

    bool IsClicked(int mouseX, int mouseY, bool MouseClicked);

    void Draw(sf::RenderWindow& window);
    void ChangePosition(float x, float y);
    void ChangeSize(float x, float y);
};

class Game{
private:
    int window_width = 800;
    int window_height = 600;

    sf::RenderWindow window;
    TextureMenager textures;

    Player player;
    Arena* currentArena = nullptr;

    Button* btnStart = nullptr;
    Button* btnMenu = nullptr;
    Button* btnSettings = nullptr;

    bool isMouseClicked_Left = false;
    bool isMouseClicked_Right = false;

public:
    int points;

    Game();
    ~Game();

    void Run();

    void DisplayMenu(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, sf::Vector2i& Mouse_pos);
    void DisplayArena(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, sf::Vector2i& Mouse_pos);
    void DisplaySettings(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, sf::Vector2i& Mouse_pos);

};
