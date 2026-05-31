#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "textureMenager.h"
#include "utils.h"
#include "player.h"
#include <fstream>

class Button;
class Player;
enum class Slots{Slot1,Slot2,Slot3};
class Settings{
private:
    sf::Sprite BackGround;
    std::map<std::string, Button*> buttons;
    std::map<std::string, sf::Text> texts;
    std::map<std::string, Button*> slots;
    Utils::Mouse& mouse;
    Utils::Menagers& menagers;
    bool SlotsVisible;
    Player& player;
    int difficulty;
    void saveGame(Slots slot);
    void loadGame();
    void setDifficulty();
public:
    Settings(Utils::Menagers& menagers, Player& player, Utils::Mouse& m);
    ~Settings();

    bool Update(Utils::Mouse& mouse);
    void Draw(sf::RenderWindow& window);
};
