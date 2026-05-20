#include "game.h"
#include "arena.h"
#include "textureMenager.h"
#include "theme.h"
#include "utils.h"

//-------------------------------------------------------
//                  CLASS GAME
//-------------------------------------------------------


Game::Game() : player(textures), shop(textures,player), settings(textures, player){
    window_width = 800;
    window_height = 600;
    menuBackGround.setTexture(textures.getMenuBackGround());
};

Game::~Game(){
    for(auto& button : buttons){
        delete button.second;
    }
}
// -------------------------------------
// PETLA GLOWNA GRY
// -------------------------------------
void Game::Run(){
    window.create(sf::VideoMode(window_width, window_height),"ARENA GAME");
    window.setFramerateLimit(60);
    // Dodanie ikony aplikacji
    sf::Image icon;
    icon.loadFromFile("img/icons/game.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    sf::Font font;
    if (!font.loadFromFile("fonts/porkybold.otf")) {
        // Zapasowy plan, gdyby PorkyBold sie nie chcial wczytac
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    GameState MenuState = GameState::Intro;

    buttons["btnStart"] = new Button("START", {275, 200}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["btnMenu"] = new Button("MENU", {275, 300}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["btnShop"] = new Button("SHOP", {275, 300}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["btnSettings"] = new Button("SETTINGS", {275, 400}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    buttons["btnExit"] = new Button("EXIT", {275, 500}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);

    while(window.isOpen()){
        sf::Event event;
        isMouseClicked_Left = false;
        isMouseClicked_Right = false;

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed){window.close();}
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){isMouseClicked_Left = true;}
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right){isMouseClicked_Right = true;}

        }
        window.clear(sf::Color(30,30,30));

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);


        if (MenuState == GameState::Arena) {
            DisplayArena(window, textures ,MenuState,mousePos);
        }
        else if(MenuState == GameState::Shop){
            DisplayShop(window, MenuState, mousePos);
        }
        else if(MenuState == GameState::Settings){
            DisplaySettings(window, MenuState,mousePos);
        }
        else if(MenuState == GameState::MainMenu){
            DisplayMenu(window, MenuState, mousePos);
        }
        else if (MenuState == GameState::Intro) {
            DisplayIntro(window, MenuState);
        }
        window.display();

    }
}
// -------------------------------------
// WYSWIETLANIE STANOW MENU
// -------------------------------------
// MENU
void Game::DisplayMenu(sf::RenderWindow& window, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    sf::Text title("The Arena", textures.getMainFont(), 60);
    Utils::CenterTextOrigin(title);
    title.setOutlineColor(sf::Color::Black);
    title.setFillColor(Theme::Text);
    title.setOutlineThickness(3.f);
    title.setPosition(400, 100);


    if(buttons["btnStart"]->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::Arena;
    }
    if(buttons["btnShop"]->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::Shop;
    }
    if(buttons["btnSettings"]->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::Settings;
    }
    if(buttons["btnExit"]->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        window.close();
    }

    window.draw(menuBackGround);
    for(auto const& button : buttons){
        button.second->Draw(window);
    }
    window.draw(title);

}
// ARENA
void Game::DisplayArena(sf::RenderWindow& window, TextureMenager& textures, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    if (currentArena == nullptr) {
                currentArena = new Arena("Arena", textures, player);
        }
        // Sprawdzamy, czy arena chce kontynuować działanie
        bool stayInArena = currentArena->Update(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left);

        if (!stayInArena) {
            delete currentArena;
            currentArena = nullptr;
            Menu_State = GameState::MainMenu;
        }
        else {
            currentArena->Draw(window);
        }
}

void Game::DisplaySettings(sf::RenderWindow& window, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    if(!settings.Update(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::MainMenu;
    }
    else{
        settings.Draw(window);
    }
}
// SHOP
void Game::DisplayShop(sf::RenderWindow& window, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    if(!shop.Update(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::MainMenu;
    }
    else{
        shop.Draw(window);
    }
}
// INTRO
void Game::DisplayIntro(sf::RenderWindow& window, GameState& Menu_State){
    // Czas wyświetlania jednego ekranu w sekundach
    const float displayTime = 1.0f;

    if(introStage >= 3){
        return;
    }

    // Inicjalizacja przy pierwszym wejściu do metody
    if (introStage == 0) {
            introSprite.setTexture(textures.getStudio()); // studio

        introClock.restart();
        introStage = 1;
    }

    // Zmiana na game name
    if (introClock.getElapsedTime().asSeconds() >= displayTime) {
        if (introStage == 1) {
            introStage = 2;
                introSprite.setTexture(textures.getGameName());

            introClock.restart();
        }
        else if (introStage == 2) {
            // Koniec intro, przełączamy stan gry na Menu Główne
            Menu_State = GameState::MainMenu;
            introStage = 3;
        }
    }

    // Rysowanie aktualnego loga na ekranie
    window.draw(introSprite);
}

