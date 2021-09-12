#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Player.h"
#include "Hero.h"

class Enemy: public Player
{
public:
    Enemy(Character *characterArr, Hero *hero_target, Vector2 pos);
    virtual Vector2 getScreenPos() override;
    virtual Vector2 getMapPos() override;
    virtual void tick(float dT) override; 
private:
    Hero *target {nullptr};
    void updatePos() override;
    Vector2 distance;
    // attack
    float attack_radius {50.f};
    float chase_radius {200.f};
    float damage {5.f};
    bool isDmgEffect {false};
    // animateDeath
    bool isAnimateDeath {false};
    int animateCount {};
    bool isCount {false};
};

#endif