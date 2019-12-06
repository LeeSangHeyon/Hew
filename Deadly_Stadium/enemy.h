#pragma once
#include "zombie.h"
#include "zombie_special.h"

#define ZOMBIE_SIZE (40) 
#define SPECIALZOMBIE_SIZE (40)

void Enemy_Init();
void Enemy_Update();
void Enemy_Draw();


ZOMBIE_BASIC* GetZombieBasic();
ZOMBIE_HAMMER* GetZombieHammer();
ZOMBIE_BASEBALL* GetBaseBallZombie();