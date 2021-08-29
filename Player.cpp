#include "Player.h"

Player::Player(Character *characterArr):
    character {characterArr}
{
    
}

void Player::tick(float dT)
{
    updatePos();
    updateFrame(dT);
    renderPlayer();
}

Vector2 Player::getWorldPos()
{
    return worldPos;
}

void Player::updateCharacterAction(int index)
{
    i = index;
    width = character[i].action.width / (character[i].maxFrame + 1);
    height = character[i].action.height;
    // frame = 0;
    // runningTime = 0;
}

void Player::updateFrame(float dT)
{
    runningTime += dT;
    if (runningTime >= updatingTime)
    {
        runningTime = 0;
        frame++;
        if (frame > character[i].maxFrame) frame = 0;
    }
}

void Player::renderPlayer()
{
    Rectangle src {frame * width, 0.f, rightLeft * width, height};
    Vector2 screenPos = getScreenPos();
    Rectangle dest {screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(character[i].action, src, dest, Vector2{}, 0.f, WHITE);
}

void Player::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Vector2 Player::getCG_pos()
{
    Vector2 screenPos = getScreenPos();
    return Vector2 {
        screenPos.x + scale * 0.5f * width,
        screenPos.y + scale * 0.5f * height
    };
}

Rectangle Player::getCollisionRec()
{
    Vector2 CG_pos = getCG_pos();
    float dim {50.f};
    return Rectangle {
        CG_pos.x - 0.5f * dim,
        CG_pos.y - 0.5f * dim,
        dim,
        dim
    };
}