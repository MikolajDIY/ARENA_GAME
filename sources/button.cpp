#include "button.h"
#include "theme.h"
//-------------------------------------------------------
//                  CLASS BUTTON
//-------------------------------------------------------

// Konstruktor glowny
Button::Button(std::string text, sf::Vector2f pos, sf::Font& font, sf::Color normalC, sf::Color hoverC){
    normalColor = normalC;
    hoverColor = hoverC;
    Position = pos;

    shape.setSize(sf::Vector2f(250, 60));
    shape.setPosition(Position);
    shape.setFillColor(normalColor);

    // Obramowanie przycisku
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(Theme::ButtonOutline);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(Theme::Text);

    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    buttonText.setPosition(Position.x + shape.getSize().x / 2.f, Position.y + shape.getSize().y / 2.f);
}

// Konstruktor uproszczony - domyslna czcionka i kolory
Button::Button(std::string text, sf::Vector2f pos, sf::Vector2f siz){
    normalColor = Theme::ButtonNormal;
    hoverColor = Theme::ButtonHover;
    Position = pos;

    shape.setSize(siz);
    shape.setFillColor(normalColor);
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(Theme::ButtonOutline);

    buttonText.setString(text);
    buttonText.setCharacterSize(siz.y/2.f);
    buttonText.setFillColor(Theme::Text);

    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width/2.f, textRect.top + textRect.height/2.f);
    buttonText.setPosition(Position.x + shape.getSize().x / 2.f, Position.y + shape.getSize().y / 2.f);
}

// -------------------------------------
// SPRAWDZENIE CZY KLIKNIETY I RYSOWANIE
// -------------------------------------
bool Button::IsClicked(int mouseX, int mouseY, bool MouseClicked){
    sf::Vector2f mousePos(static_cast<float>(mouseX), static_cast<float>(mouseY));
    bool Hoverd = shape.getGlobalBounds().contains(mousePos);

    if(Hoverd){
        shape.setFillColor(hoverColor);
    }
    else{
        shape.setFillColor(normalColor);
    }
    return Hoverd && MouseClicked;
}

void Button::Draw(sf::RenderWindow& window){
    window.draw(shape);
    window.draw(buttonText);
}

// -------------------------------------
// DODATKOWE FUNKCJE - MODYFIKACJE ISTNIEJACYCH
// -------------------------------------
void Button::ChangePosition(float x, float y){
    Position.x = x;
    Position.y = y;
    shape.setPosition(Position);

    buttonText.setPosition(
        Position.x + (shape.getSize().x / 2.f), Position.y + (shape.getSize().y / 2.f)
    );
}
void Button::ChangeSize(float x, float y){
    shape.setSize(sf::Vector2f(x,y));
    fontSize = y/2;
    buttonText.setCharacterSize(fontSize);
    // Zmiana rozmiaru tekstu
    int fontSize = static_cast<int>(y / 2);
    buttonText.setCharacterSize(fontSize);
    // Obliczenie nowego srodka tekstu
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    buttonText.setPosition(
        Position.x + (shape.getSize().x / 2.0f),
        Position.y + (shape.getSize().y / 2.0f)
    );
}

void Button::ChangeTextColor(sf::Color color){
    buttonText.setFillColor(color);
}


