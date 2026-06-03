#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "textureMenager.h"
#include "utils.h"
#include "player.h"
#include <fstream>
#include <sstream>

class Button;
class Player;
enum class Slots{Slot1,Slot2,Slot3};
enum class Difficulties;
class Settings{
private:
    sf::Sprite BackGround;
    std::map<std::string, Button*> buttons;
    std::map<std::string, sf::Text> texts;
    std::map<std::string, Button*> save_slots;
    std::map<std::string, Button*> load_slots;
    std::map<std::string, Button*> DifficultyButtons;
    Utils::Mouse& mouse;
    Utils::Menagers& menagers;
    bool SaveSlotsVisible;
    bool LoadSlotsVisible;
    bool DiffButtonsVisible;
    Player& player;
    void saveGame(Slots slot);
    void loadGame(Slots slot);
    void setDifficulty(Difficulties newDifficulty);
public:
    Settings(Utils::Menagers& menagers, Player& player, Utils::Mouse& m);
    ~Settings();

    bool Update(Utils::Mouse& mouse);
    void Draw(sf::RenderWindow& window);
};
