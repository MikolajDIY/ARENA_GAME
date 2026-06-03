#include "settings.h"
#include "button.h"
#include "game.h"
#include "theme.h"
#include "utils.h"
#include "stats.h"
// -------------------------------------
// CLASS SETTINGS
// -------------------------------------

 Settings::Settings(Utils::Menagers& menagers, Player& player, Utils::Mouse& m)
  : mouse(m),
   player(player),
   menagers(menagers){

    BackGround.setTexture(menagers.tex.getSettingsBackGround());
    buttons["BackToMenu"] = new Button("Menu", {10,10},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["BackToMenu"]->ChangeSize(80,40);
    buttons["Save"] = new Button("Save",{50,200},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["Save"]->ChangeSize(200,80);
    buttons["Load"] = new Button("Load",{300,200},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["Load"]->ChangeSize(200,80);
    buttons["Difficulty"] = new Button("Difficulty",{550,200},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["Difficulty"]->ChangeSize(200,80);
    save_slots["Slot1"] = new Button("Game save 1",{80,290},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    save_slots["Slot1"]->ChangeSize(140,40);
    save_slots["Slot2"] = new Button("Game save 2",{80,340},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    save_slots["Slot2"]->ChangeSize(140,40);
    save_slots["Slot3"] = new Button("Game save 3",{80,390},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    save_slots["Slot3"]->ChangeSize(140,40);
    load_slots["Slot1"] = new Button("Game save 1",{330,290},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    load_slots["Slot1"]->ChangeSize(140,40);
    load_slots["Slot2"] = new Button("Game save 2",{330,340},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    load_slots["Slot2"]->ChangeSize(140,40);
    load_slots["Slot3"] = new Button("Game save 3",{330,390},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    load_slots["Slot3"]->ChangeSize(140,40);
    DifficultyButtons["Easy"] = new Button("Easy",{580,290},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    DifficultyButtons["Easy"]->ChangeSize(140,40);
    DifficultyButtons["Medium"] = new Button("Medium",{580,340},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    DifficultyButtons["Medium"]->ChangeSize(140,40);
    DifficultyButtons["Hard"] = new Button("Hard",{580,390},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    DifficultyButtons["Hard"]->ChangeSize(140,40);

    texts["Settings"] = sf::Text("Settings",menagers.tex.getMainFont(), 40);
    Utils::CenterTextOrigin(texts["Settings"]);
    texts["Settings"].setPosition(400,40);
    SaveSlotsVisible=false;
    LoadSlotsVisible=false;
    DiffButtonsVisible=false;
 }

 Settings::~Settings(){
    for (auto const& button : buttons){
        delete button.second;
    }
    buttons.clear();
    for (auto const& button : save_slots){
        delete button.second;
    }
    save_slots.clear();
    for (auto const& button : load_slots){
        delete button.second;
    }
    load_slots.clear();
    for (auto const& button : DifficultyButtons){
        delete button.second;
    }
    DifficultyButtons.clear();
 }




// -------------------------------------
// WYSWIETLANIE USTAWIEN
// -------------------------------------
bool Settings::Update(Utils::Mouse& m){
    if (buttons["BackToMenu"]->IsClicked(m)) {
        return false;
    }
    if (buttons["Save"]->IsClicked(m))
    {
        SaveSlotsVisible=!SaveSlotsVisible;
    }
    if (buttons["Load"]->IsClicked(m))
    {
        LoadSlotsVisible=!LoadSlotsVisible;
    }
    if (buttons["Difficulty"]->IsClicked(m))
    {
        DiffButtonsVisible=!DiffButtonsVisible;
    }
    if(SaveSlotsVisible){
        if(save_slots["Slot1"]->IsClicked(m))
        {
            saveGame(Slots::Slot1);
            SaveSlotsVisible=!SaveSlotsVisible;
        }
        if(save_slots["Slot2"]->IsClicked(m))
        {
            saveGame(Slots::Slot2);
            SaveSlotsVisible=!SaveSlotsVisible;
        }
        if(save_slots["Slot3"]->IsClicked(m))
        {
            saveGame(Slots::Slot3);
            SaveSlotsVisible=!SaveSlotsVisible;
        }

    }
    if(LoadSlotsVisible){
        if(load_slots["Slot1"]->IsClicked(m))
        {
            loadGame(Slots::Slot1);
            LoadSlotsVisible=!LoadSlotsVisible;
        }
        if(load_slots["Slot2"]->IsClicked(m))
        {
            loadGame(Slots::Slot2);
            LoadSlotsVisible=!LoadSlotsVisible;
        }
        if(load_slots["Slot3"]->IsClicked(m))
        {
            loadGame(Slots::Slot3);
            LoadSlotsVisible=!LoadSlotsVisible;
        }

    }
    if(DiffButtonsVisible){
        if(DifficultyButtons["Easy"]->IsClicked(m))
        {
            setDifficulty(Difficulties::easy);
            DiffButtonsVisible=!DiffButtonsVisible;
        }
        if(DifficultyButtons["Medium"]->IsClicked(m))
        {
            setDifficulty(Difficulties::medium);
            DiffButtonsVisible=!DiffButtonsVisible;
        }
        if(DifficultyButtons["Hard"]->IsClicked(m))
        {
            setDifficulty(Difficulties::hard);
            DiffButtonsVisible=!DiffButtonsVisible;
        }
    }
    mouse = m;
    return true;
 }

void Settings::Draw(sf::RenderWindow& window){
    window.draw(BackGround);

    for(auto const& button : buttons){
        button.second->Draw(window);
    }
    for(auto const& button : texts){
        window.draw(button.second);
    }
    if(SaveSlotsVisible)
    {
        for(auto const& button : save_slots){
        button.second->Draw(window);
    }
    }
    if(LoadSlotsVisible)
    {
        for(auto const& button : load_slots){
        button.second->Draw(window);
    }
    }
    if(DiffButtonsVisible)
    {
        for(auto const& button : DifficultyButtons){
        button.second->Draw(window);
    }
    }

 }

void Settings::saveGame(Slots slot)
{
    std::string filename = "Save_" + std::to_string(static_cast<int>(slot))+".txt";
    std::ofstream file(filename);
    if(!file.is_open())
    {
        menagers.msg.add("Failed to create save",MessageType::Error,Utils::TimeOfMessage);
        return;
    }
    file<<player.getname()<<'\n';
    file<<player.getGold()<<'\n';
    file<<player.getPoints()<<'\n';
    file<<static_cast<int>(Stats::difficulty)<<'\n';

    auto swords = player.getUnlockedSwords();
    auto armors = player.getUnlockedArmors();
    file<<swords.size()<<'\n';
    for(auto const& sword:swords)
    {
        file<<static_cast<int>(sword.first)<<" "<<sword.second<<'\n';
    }
    file<<armors.size()<<'\n';
    for(auto const& armor:armors)
    {
        file<<static_cast<int>(armor.first)<<" "<<armor.second<<'\n';
    }
    file<<static_cast<int>(player.getSword())<<'\n';
    file<<static_cast<int>(player.getArmor())<<'\n';
    file.close();
    menagers.msg.add("Game saved",MessageType::Success,Utils::TimeOfMessage);
}
void Settings::loadGame(Slots slot)
{
    std::string filename = "Save_" + std::to_string(static_cast<int>(slot))+".txt";
    std::ifstream file(filename);
    if(!file.is_open())
    {
        menagers.msg.add("Failed to load save",MessageType::Error,Utils::TimeOfMessage);
        return;
    }
    std::string line;
    std::getline(file,line);
    player.setName(line);

    std::getline(file,line);
    player.setGold(std::stoi(line));

    std::getline(file,line);
    player.setPoints(std::stoi(line));

    std::getline(file,line);
    Stats::difficulty=static_cast<Difficulties>(std::stoi(line));



    std::getline(file,line);
    int numberofswords = std::stoi(line);
    int type;
    bool status;
    for(int i=0;i<numberofswords;i++)
    {
        std::getline(file,line);
        std::stringstream ss(line);
        ss>>type>>status;
        player.setUnlockedSwords(static_cast<SwordsTypes>(type),status);
    }
    std::getline(file,line);
    int numberofarmors = std::stoi(line);
    for(int i=0;i<numberofarmors;i++)
    {
        std::getline(file,line);
        std::stringstream ss(line);
        ss>>type>>status;
        player.setUnlockedArmors(static_cast<ArmorsTypes>(type),status);
    }
    std::getline(file,line);
    player.setSword(static_cast<SwordsTypes>(std::stoi(line)));

    std::getline(file,line);
    player.setArmor(static_cast<ArmorsTypes>(std::stoi(line)));
    menagers.msg.add("Save loaded succesfully",MessageType::Success,Utils::TimeOfMessage);
}

void Settings::setDifficulty(Difficulties difficulty)
{
    Stats::difficulty=difficulty;
    std::string message = "Difficulty changed to ";
    if(difficulty==Difficulties::easy){message+="easy";}
    else if (difficulty==Difficulties::medium){message+="medium";}
    else if (difficulty==Difficulties::hard){message+="hard";}
    menagers.msg.add(message,MessageType::Warning,Utils::TimeOfMessage);
}
