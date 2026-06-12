#include "messages.h"
//-----------------------------------
//      MESSAGE MENAGER
//-----------------------------------

MessageMenager::MessageMenager(TextureMenager& tex) : textures(tex){}

// DODAWANIE KOMUNIKATOW DO WYSWIETLANIA
void MessageMenager::add(std::string name, MessageType mtype, float tim, sf::Color color, sf::Vector2f pos, float siz){
    Utils::GameMessage msg;
    msg.type = mtype;
    msg.info = name;
    msg.timeOfLife = tim;
    msg.clock.restart();
    msg.textColor = color;
    msg.position = pos;
    msg.size = siz;

    messagess.push_back(msg);
}
// USUWANIE PRZEDAWNIONYCH KOMUNIKATOW
void MessageMenager::update(){
    messagess.erase(std::remove_if(messagess.begin(),messagess.end(),[](Utils::GameMessage msg){
                                    return msg.clock.getElapsedTime().asSeconds() >= msg.timeOfLife;
                                   }), messagess.end());
}
// RYSOWANIE
void MessageMenager::Draw(sf::RenderWindow& window){
    int number = 0;
    int numberSpecial =0;
    float lastSize = 0;
    float lastSizeSpecial =0;

    std::map<std::string, int> floatingOffsets;

    for(auto& msg : messagess){
        sf::Text text(msg.info, textures.getMainFont(), msg.size);
        if(msg.type == MessageType::GameInfo){
                text.setFont(textures.getGameOverFont());
                text.setCharacterSize(msg.size);
        }

        if(number == 0){lastSize = msg.size;}
        if(numberSpecial == 0){lastSizeSpecial = msg.size;}

        Utils::ObjectFormatter<sf::Text>::formatText(text);

        switch(msg.type){
        case MessageType::Error:
            text.setFillColor(sf::Color::Red);
            break;

        case MessageType::Warning:
            text.setFillColor(sf::Color::Yellow);
            break;

        case MessageType::Success:
            text.setFillColor(sf::Color::Green);
            break;

        case MessageType::Damage:
            text.setFillColor(sf::Color::Red);
            break;

        case MessageType::Heal:
            text.setFillColor(sf::Color::Green);
            break;
        }

        if(msg.type == MessageType::GameInfo){
            text.setFillColor(msg.textColor);
            text.setPosition(msg.position + sf::Vector2f(0.0f, 1.1f * numberSpecial * lastSizeSpecial));
            lastSizeSpecial = msg.size;
            numberSpecial ++;
        }
        else if(msg.type == MessageType::Damage || msg.type == MessageType::Heal) {
            std::string posKey = std::to_string(msg.position.x) + "," + std::to_string(msg.position.y);
            int activeTextsAtThisPos = floatingOffsets[posKey];

            text.setPosition(msg.position + sf::Vector2f(-10.f, -1.1f * activeTextsAtThisPos * msg.size));

            floatingOffsets[posKey]++;
        }
        else {
            if(number == 0){ lastSize = msg.size; }
            text.setPosition(400.f, 500.f + (number * lastSize));
            lastSize = msg.size;
            number++;
        }

        window.draw(text);
    }
}

