#pragma once
#include "skeleton.h"

Skeleton::Skeleton(TextureMenager& textures) : Enemy(textures){
    enemySprite.setTexture(textures.getSkeleton());
    name = "Skeleton";
    gold = 10;
    points = 50;
}
