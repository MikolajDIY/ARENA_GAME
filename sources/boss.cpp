#pragma once
#include "boss.h"

Boss::Boss(TextureMenager& textures) : Enemy(textures){
    enemySprite.setTexture(textures.getBoss());
    name = "THE UNDYING EMPEROR";
    gold = 1000;
    points = 5000;
}

