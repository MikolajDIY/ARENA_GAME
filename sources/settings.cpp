#include "settings.h"
#include "button.h"
#include "theme.h"
#include "utils.h"
// -------------------------------------
// CLASS SETTINGS
// -------------------------------------

 Settings::Settings(TextureMenager& textures, Player& player){
    BackGround.setTexture(textures.getSettingsBackGround());
    buttons["BackToMenu"] = new Button("Menu", {10,10},textures.getMainFont(),Theme::ButtonNormal,Theme::ButtonHover);
    buttons["BackToMenu"]->ChangeSize(80,40);

    texts["Settings"] = sf::Text("Settings",textures.getMainFont(), 40);
    Utils::CenterTextOrigin(texts["Settings"]);
    texts["Settings"].setPosition(400,40);
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
bool Settings::Update(int mouseX, int mouseY, bool isClicked){
    if (buttons["BackToMenu"]->IsClicked(mouseX, mouseY, isClicked)) {
        return false;
    }
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
