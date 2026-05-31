#include "settings.h"
#include "button.h"
#include "game.h"
#include "theme.h"
#include "utils.h"
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
    buttons["Save"] = new Button("Save",{280,200},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["Save"]->ChangeSize(250,80);
    buttons["Load"] = new Button("Load",{280,300},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["Load"]->ChangeSize(250,80);
    buttons["Difficulty"] = new Button("Difficulty",{280,400},menagers.tex.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["Difficulty"]->ChangeSize(250,80);


    texts["Settings"] = sf::Text("Settings",menagers.tex.getMainFont(), 40);
    Utils::CenterTextOrigin(texts["Settings"]);
    texts["Settings"].setPosition(400,40);
    difficulty=1;
 }

 Settings::~Settings(){
    for (auto const& button : buttons){
        delete button.second;
    }
    buttons.clear();
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
        saveGame();
    }
    if (buttons["Load"]->IsClicked(m))
    {
        menagers.msg.add("[TEST] kliknieto load",MessageType::Success,Utils::TimeOfMessage);
    }
    if (buttons["Difficulty"]->IsClicked(m))
    {
        menagers.msg.add("[TEST] kliknieto difficulty",MessageType::Success,Utils::TimeOfMessage);
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
 }
void Settings::saveGame()
{
    std::ofstream file("Save.txt");
    if(!file.is_open())
    {
        menagers.msg.add("Failed to create save",MessageType::Error,Utils::TimeOfMessage);
        return;
    }
    file<<player.getname()<<'\n';
    file<<player.getGold()<<'\n';
    file<<player.getPoints()<<'\n';
    file<<difficulty<<'\n';

    file<<static_cast<int>(player.getSword())<<'\n';
    file<<static_cast<int>(player.getArmor())<<'\n';

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
    file.close();
    menagers.msg.add("Game saved",MessageType::Success,Utils::TimeOfMessage);
}
