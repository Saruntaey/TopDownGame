#ifndef _HELPER_H_
#define _HELPER_H_
#include "raylib.h"
#include <string>
#include "character.h"
#include "Hero.h"
#include "Enemy.h"


// function prototype
void loadCharacter(Character *goblin, Character *mushroom, Character *skeleton, Character *knight);
void UnloadCharacter(Character *goblin, Character *mushroom, Character *skeleton, Character *knight);
void print_health(Hero *kn);
void plotMiniMap(Hero *p, Enemy *enemies[], int enemiesSize, Texture *map, float mapScale, float windowWidth, float windowHeight);

#endif