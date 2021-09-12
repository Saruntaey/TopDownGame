#include "Hero.h"

Hero::Hero(Character *characterArr, Texture2D *sword, int winWidth, int winHeight):
    Player(characterArr),
    windowWidth {winWidth},
    windowHeight {winHeight},
    weapon {sword}
{
    scale = 4.f;
}

void Hero::tick(float dT)
{
    Player::tick(dT);
    renderWeapon();
}

Vector2 Hero::getScreenPos()
{
    return Vector2 {
        windowWidth/2.f - scale * width/2.f,
        windowHeight/2.f - scale * height/2.f
    };
}

Vector2 Hero::getMapPos()
{
    return Vector2Add(worldPos, getCG_pos());
}

void Hero::updatePos()
{
    if (IsKeyDown(KEY_A)) velocity.x += -1;
    if (IsKeyDown(KEY_D)) velocity.x += 1;
    if (IsKeyDown(KEY_W)) velocity.y += -1;
    if (IsKeyDown(KEY_S)) velocity.y += 1;

    if (Vector2Length(velocity) != 0.f)
    {
        rightLeft = velocity.x >= 0.f ? 1.f : -1.f;
        velocity = Vector2Scale(Vector2Normalize(velocity), speed);
        updateCharacterAction(1);
    }
    else
    {
        updateCharacterAction(0);    
    }

    worldPosLastFrame = worldPos;
    worldPos = Vector2Add(worldPos, velocity);
    velocity = {};
}

void Hero::takeDamage(float dmg)
{
    health -= dmg;
    if (health <= 0)
    {
        setAlive(false);
    }
}

void Hero::renderWeapon()
{
    Vector2 origin {};
    Vector2 offset {};
    float rotation {};
    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon->height * weapon_scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon->height * weapon_scale,
            weapon->width * weapon_scale,
            weapon->height * weapon_scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f: 0.f;
    }
    else
    {
        origin = {weapon->width * weapon_scale, weapon->height * weapon_scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon->width * weapon_scale,
            getScreenPos().y + offset.y - weapon->height * weapon_scale,
            weapon->width * weapon_scale,
            weapon->height * weapon_scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f: 0.f;
    }


    // draw the sword
    Rectangle source {0.f, 0.f, weapon->width * rightLeft, static_cast<float>(weapon->height)};
    Vector2 screenPos = getScreenPos();
    Rectangle dest {screenPos.x + offset.x, screenPos.y + offset.y, weapon->width * weapon_scale, weapon->height * weapon_scale};
    DrawTexturePro(*weapon, source, dest, origin, rotation, WHITE);
}