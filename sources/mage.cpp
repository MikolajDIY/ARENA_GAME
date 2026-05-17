#pragma once
#include "mage.h"

Mage::Mage(TextureMenager& textures) : Enemy(textures){
    enemySprite.setTexture(textures.getMage());
    name = "Mage";
    gold = 50;
    points = 200;
}

