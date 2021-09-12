#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "raylib.h"
#include "character.h"
class Player
{
public:
    Player(Character *characterArr);
    virtual void tick(float dT);
    void undoMovement();
    Vector2 getWorldPos();
    virtual Vector2 getScreenPos() = 0;
    Vector2 getCG_pos();
    virtual Vector2 getMapPos() = 0;
    Rectangle getCollisionRec();
    bool getAlive() { return alive; }
    void setAlive(bool a) {alive = a;}
protected:
    Character *character;
    int i = 0;
    float width = character[i].action.width / (character[i].maxFrame + 1);
    float height = character[i].action.height;
    float scale {2.f};
    int frame {};
    float updatingTime = 1.f/12.f;
    float runningTime {};
    // 1 face right, -1 face left
    float rightLeft {1.f};
    float speed {4.f};
    Vector2 velocity {};
    Vector2 worldPos {};
    Vector2 worldPosLastFrame {};
    void updateCharacterAction(int index);
    virtual void updatePos() = 0;
private:
    void updateFrame(float dT);
    void renderPlayer();
    bool alive {true};
};

#endif