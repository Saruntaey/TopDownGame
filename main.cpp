#include "raylib.h"
#include "helper.h"
#include "Hero.h"
#include "Enemy.h"

int main()
{
    const int windowWidth {384 * 2};
    const int windowHeight {384 * 2};

    InitWindow(windowWidth, windowHeight, "Top down game");
    SetTargetFPS(60);

    // load map
    Texture2D map {LoadTexture("nature_tileset/OpenWorldMap.png")};
    Vector2 mapPos {};
    float mapScale {4.f};

    // load character
    Character goblin[4];
    Character mushroom[4];
    Character skeleton[4];
    Character knight[2];
    loadCharacter(goblin, mushroom, skeleton, knight);

    // load weapon
    Texture2D sword {LoadTexture("weapons/sword.png")};

    // create player
    Hero kn {knight, &sword, windowWidth, windowHeight};
    
    Enemy gb {goblin, &kn, Vector2 {1000.f, 200.f}};
    Enemy mr {mushroom, &kn, Vector2 {800.f, 300.f}};
    Enemy sk {skeleton, &kn, Vector2 {500.f, 900.f}};
    
    Enemy *enemies[] {
        &gb,
        &mr,
        &sk
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // draw map
        mapPos = Vector2Scale(kn.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);

        if (!kn.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }

        print_health(&kn);

        kn.tick(GetFrameTime());
        // check map bound
        Vector2 kn_wordPos = kn.getWorldPos();
        if (kn_wordPos.x < 0.f ||
            kn_wordPos.y < 0.f ||
            kn_wordPos.x > mapScale * map.width - windowWidth ||
            kn_wordPos.y > mapScale * map.height - windowHeight)
        {
            kn.undoMovement();
        }

        for (auto enemy: enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // check sword collision
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy: enemies)
            {
                if(CheckCollisionRecs(enemy->getCollisionRec(), kn.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
            
        }
        // Draw mimimap
        plotMiniMap(&kn, enemies, 3, &map, mapScale, windowWidth, windowHeight);
        EndDrawing();
    }
    UnloadTexture(sword);
    UnloadCharacter(goblin, mushroom, skeleton, knight);
    UnloadTexture(map);
    CloseWindow();
}