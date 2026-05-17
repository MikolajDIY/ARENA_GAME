#include "arena.h"
#include "textureMenager.h"
#include "player.h"
#include "theme.h"
#include "skeleton.h"
#include "zombie.h"
#include "mage.h"
#include "boss.h"

Arena::Arena(std::string arenaName, TextureMenager& textures, Player& mainPlayer) : textures(textures), player(mainPlayer){
    name = arenaName;
    currentState = TurnState::PlayerMove;
    btnBackToMenu = new Button("MENU", {10,10}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnBackToMenu->ChangeSize(90,40);
    arenaBackGround.setTexture(textures.getArenaBackGround());

    // Przykladowo dodany wrog
    enemies.push_back(new Zombie(textures)); // Moze lepiej trzymac ich w std::map ?
    enemies[0]->Update(320,250);
}

Arena::~Arena(){
    delete btnBackToMenu;
}

void Arena::Fight(){
    // Mechanika walki
}

// -------------------------------------
// RYSOWANIE ARENY
// -------------------------------------
bool Arena::Update(int mouseX, int mouseY, bool isClicked) {
    if (btnBackToMenu->IsClicked(mouseX, mouseY, isClicked)) {
        return false;
    }

    Fight(); // Logika walki
    return true;
}

void Arena::Draw(sf::RenderWindow& window){
    // Rysowanie Areny
    window.draw(arenaBackGround);
    // Rysowanie Przeciwnikow
    for(auto const& enemy : enemies){  // Przy zmianie przechowywania na std::map ZMIENIC
        enemy->Draw(window);
    }
    // Rysowania Gracza
    player.Update();
    player.Draw(window);

    //Rysowanie Przyciskow
    btnBackToMenu->Draw(window);
}



