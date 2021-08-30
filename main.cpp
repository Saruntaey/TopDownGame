#include "raylib.h"
#include "helper.h"
#include "Hero.h"
#include "Enemy.h"

bool reqWindowClose {false};
bool isFirstOpen {true};


int main()
{
    const int windowWidth {384 * 2};
    const int windowHeight {384 * 2};

    InitWindow(windowWidth, windowHeight, "Top down game");
    SetTargetFPS(60);

    while (!reqWindowClose)
    {
        gameIntro(windowWidth, windowHeight, isFirstOpen, reqWindowClose);
        gameLogic(windowHeight, windowHeight, reqWindowClose);
        gameOver(reqWindowClose);
    }
    CloseWindow();
}