#include "Enemy.h"

Enemy::Enemy(Character *characterArr, Hero *hero_target, Vector2 pos):
    Player(characterArr),
    target {hero_target}
{
    speed = 3.5f;
    worldPos = pos;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

Vector2 Enemy::getMapPos()
{
    return Vector2Add(Vector2Subtract(getCG_pos(), target->getCG_pos()), target->getMapPos());
}

void Enemy::updatePos()
{
    distance = Vector2Subtract(target->getCG_pos(), getCG_pos());
    velocity = distance;
    if (!getAlive())
    {   
        // death
        if (!isAnimateDeath)
        {
            velocity = {};
            updateCharacterAction(3);
            if (frame == character[i].maxFrame)
            {
                if (!isCount)
                {
                    animateCount++;
                    isCount = true;
                }
            }
            else
            {
                isCount = false;
            }

            if (animateCount == 3)
            {
                isAnimateDeath = true;
            }
        }
        else
        {
            return;
        }
    }
    else if (Vector2Length(distance) <= attack_radius)
    {
        // attack
        rightLeft = distance.x >= 0.f ? 1.f : -1.f;
        velocity = {};
        updateCharacterAction(2);
        if (frame == character[i].maxFrame)
        {
            if (!isDmgEffect)
            {
                target->takeDamage(damage);
                isDmgEffect = true;
            }
        }
        else
        {
            isDmgEffect = false;
        }
    }
    else if (Vector2Length(velocity) != 0.f && Vector2Length(distance) <= chase_radius)
    {
        // chasing
        rightLeft = velocity.x >= 0.f ? 1.f : -1.f;
        velocity = Vector2Scale(Vector2Normalize(velocity), speed);
        updateCharacterAction(1);
    }
    else
    {
        // idle
        updateCharacterAction(0);
        velocity = {};    
    }

    worldPosLastFrame = worldPos;
    worldPos = Vector2Add(worldPos, velocity);
    velocity = {};
}

void Enemy::tick(float dT)
{
    if (isAnimateDeath)
    {
        return;
    }
    Player::tick(dT);
}