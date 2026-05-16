#include "button.h"
#include "theme.h"
//-------------------------------------------------------
//                  CLASS BUTTON
//-------------------------------------------------------


Button::Button(std::string text, sf::Vector2f pos, sf::Font& font, sf::Color normalC, sf::Color hoverC){
    normalColor = normalC;
    hoverColor = hoverC;
    Position = pos;

    shape.setSize(sf::Vector2f(250, 60));
    shape.setPosition(Position);
    shape.setFillColor(normalColor);

    // Obramowanie przycisku
    shape.setOutlineThickness(3.f);
    shape.setOutlineColor(sf::Color(100, 70, 50));

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(Theme::Text);

    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(Position.x + shape.getSize().x / 2.0f, Position.y + shape.getSize().y / 2.0f);
}

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


