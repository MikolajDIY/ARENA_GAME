#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "utils.h"
#include "textureMenager.h"

enum class MessageType{Error, Warning, Success, GameInfo, Damage, Heal};

class MessageMenager{
private:
    TextureMenager& textures;
    std::vector<Utils::GameMessage> messagess;
public:
    MessageMenager(TextureMenager& tex);

    void add(std::string text, MessageType mtype, float tim, sf::Color color = sf::Color::White, sf::Vector2f pos = sf::Vector2f(0,0), float siz = 15);
    void update();
    void Draw(sf::RenderWindow& window);
};
