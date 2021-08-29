#ifndef _HERO_H_
#define _HERO_H_
#include "raylib.h"
#include "raymath.h"
#include "Player.h"

class Hero: public Player
{
public:
    Hero(Character *characterArr, Texture2D *sword, int winWidth, int winHeight);
    virtual Vector2 getScreenPos() override;
    virtual Vector2 getMapPos() override;
    float getHealth() { return health; }
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    void takeDamage(float dmg);
    void tick(float dT) override;
private:
    int windowWidth;
    int windowHeight;
    void updatePos() override;
    float health {100};
    Texture2D *weapon {};
    float weapon_scale {4.f};
    Rectangle weaponCollisionRec {};
    void renderWeapon();
};

#endif