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
    delete btnMenu;
    delete btnSettings;
    delete btnStart;
    delete btnExit;
}

void Game::Run(){
    window.create(sf::VideoMode(window_width, window_height),"ARENA GAME");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("fonts/porkybold.otf")) {
        // Zapasowy plan, gdyby PorkyBold sie nie chcial wczytac
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    GameState MenuState = GameState::Intro;

    btnStart = new Button("START", {275, 200}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnMenu = new Button("MENU", {275, 300}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnShop = new Button("SHOP", {275, 300}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnSettings = new Button("SETTINGS", {275, 400}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);
    btnExit = new Button("EXIT", {275, 500}, textures.getMainFont(), Theme::ButtonNormal, Theme::ButtonHover);

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

void Game::DisplayMenu(sf::RenderWindow& window, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    sf::Text title("The Arena", textures.getMainFont(), 60);
    Utils::CenterTextOrigin(title);
    title.setOutlineColor(sf::Color::Black);
    title.setFillColor(Theme::Text);
    title.setOutlineThickness(3.f);
    title.setPosition(400, 100);


    if(btnStart->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::Arena;
    }
    if(btnShop->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::Shop;
    }
    if(btnSettings->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::Settings;
    }
    if(btnExit->IsClicked(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        window.close();
    }

    window.draw(menuBackGround);
    btnStart->Draw(window);
    btnShop->Draw(window);
    btnSettings->Draw(window);
    btnExit->Draw(window);
    window.draw(title);

}

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

void Game::DisplayShop(sf::RenderWindow& window, GameState& Menu_State, sf::Vector2i& Mouse_pos){
    if(!shop.Update(Mouse_pos.x, Mouse_pos.y, isMouseClicked_Left)){
        Menu_State = GameState::MainMenu;
    }
    else{
        shop.Draw(window);
    }
}

void Game::DisplayIntro(sf::RenderWindow& window, GameState& Menu_State){
    // Czas wyświetlania jednego ekranu w sekundach
    const float displayTime = 1.0f;

    // Inicjalizacja przy pierwszym wejściu do metody
    if (!isIntroInitialized) {
            introSprite.setTexture(textures.getStudio()); // studio

        introClock.restart();
        isIntroInitialized = true;
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
        }
    }

    // Rysowanie aktualnego loga na ekranie
    window.draw(introSprite);
}

