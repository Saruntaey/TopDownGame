#include "helper.h"

void loadCharacter(Character *goblin, Character *mushroom, Character *skeleton, Character *knight)
{
    size_t characterTot = 4;

    std::string goblin_file[] = {"Idle", "Run", "Attack", "Death"};
    int goblin_maxFrame[] = {3, 7, 7, 3};
    for (size_t i = 0; i < characterTot; i++)
    {
        std::string fileName = "characters/Goblin/" + goblin_file[i] + ".png";
        goblin[i] = Character {LoadTexture(fileName.c_str()), goblin_maxFrame[i]};
    }

    std::string mushroom_file[] = {"Idle", "Run", "Attack", "Death"};
    int mushroom_maxFrame[] = {3, 7, 7, 3};
    for (size_t i = 0; i < characterTot; i++)
    {
        std::string fileName = "characters/Mushroom/" + mushroom_file[i] + ".png";
        mushroom[i] = Character {LoadTexture(fileName.c_str()), mushroom_maxFrame[i]};
    }

    std::string skeleton_file[] = {"Idle", "Walk", "Attack", "Death"};
    int skeleton_maxFrame[] = {3, 3, 7, 3};
    for (size_t i = 0; i < characterTot; i++)
    {
        std::string fileName = "characters/Skeleton/" + skeleton_file[i] + ".png";
        skeleton[i] = Character {LoadTexture(fileName.c_str()), skeleton_maxFrame[i]};
    }

    std::string knight_file[] = {"Idle", "Run"};
    int knight_maxFrame[] = {5, 5};
    for (size_t i = 0; i < 2; i++)
    {
        std::string fileName = "characters/Knight/" + knight_file[i] + ".png";
        knight[i] = Character {LoadTexture(fileName.c_str()), knight_maxFrame[i]};
    }    
}

void UnloadCharacter(Character *goblin, Character *mushroom, Character *skeleton, Character *knight)
{
    for(size_t i = 0; i < 4; i++)
    {
        UnloadTexture(goblin[i].action);
        UnloadTexture(mushroom[i].action);
        UnloadTexture(skeleton[i].action);
        if (i < 2)
        {
            UnloadTexture(knight[i].action);
        }
    }
}

void print_health(Hero *kn)
{
    std::string knightsHealth = "Health: ";
    knightsHealth.append(std::to_string(kn->getHealth()), 0, 5);
    DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
}

void plotMiniMap(Hero *p, Enemy *enemies[], int enemiesSize, Texture *map, float mapScale, float windowWidth, float windowHeight)
{   
    const int miniMapWidth {150};
    const int miniMapHeight {150};
    
    Vector2 miniMapPos = {
        windowWidth - miniMapWidth,
        windowHeight - miniMapHeight,
    };

    float mapWidth = map->width;
    // draw minimap
    float miniMapScale {miniMapWidth / mapWidth};
    DrawTextureEx(*map, miniMapPos, 0.f, miniMapScale, WHITE);

    // mark hero
    float mapProportion { miniMapWidth / (mapWidth * mapScale) };
    Vector2 p_mini = Vector2Add(Vector2Scale(p->getMapPos(), mapProportion), miniMapPos);
    DrawCircle(p_mini.x, p_mini.y, 5.f, BLUE);

    // mark enemies
    for (int i = 0; i < enemiesSize; i++)
    {
        if (enemies[i]->getAlive())
        {
            Vector2 e_mini = Vector2Add(Vector2Scale(enemies[i]->getMapPos(), mapProportion), miniMapPos);
            DrawCircle(e_mini.x, e_mini.y, 5.f, RED);
        }
        
    }
    
}

void gameIntro(int windowWidth, int windowHeight, bool &isFirstOpen, bool &reqWindowClose)
{
    if (!isFirstOpen) return;
    // load map
    Texture2D map {LoadTexture("nature_tileset/OpenWorldMap.png")};
    float mapScale {4.f};
    Vector2 mapPos {-map.width/2.f * mapScale, 0.f};
   

    // load knight
    Texture2D knight {LoadTexture("characters/Knight/Run.png")};
    float scale {4.f};
    
    int frame {};
    int frameMax {5};
    float width {static_cast<float>(knight.width)/(frameMax + 1)};
    float height {static_cast<float>(knight.height)};
    float updatingTime {1.f/12.f};
    float runningTime {};
    // 1 facing right, -1 facing left
    float rightLeft {1.f};
    float speed {160.f};
    float offset {50.f};

    float leftBound {offset};
    float rightBound {windowWidth - (offset + width * scale)};
    float x_pos {leftBound};
    while (true)
    {
        if (WindowShouldClose())
        {   
            reqWindowClose = true;
            break;
        }
        if (IsKeyDown(KEY_SPACE))
        {
            isFirstOpen = false;
            break;
        } 
        
        BeginDrawing();
        ClearBackground(WHITE);
        // draw map
        DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);
        // draw knight
        float dT = GetFrameTime();
        runningTime += dT;
        x_pos += speed * dT;
        if (x_pos < leftBound || x_pos > rightBound)
        {
            speed *= -1;
        }
        rightLeft = speed > 0 ? 1.f : -1.f;
        if (runningTime >= updatingTime)
        {
            runningTime = 0;
            frame++;
            if (frame > frameMax) frame = 0;
        }
        Rectangle src {frame * width, 0.f, rightLeft * width, height};
        Rectangle dest {x_pos, windowHeight - (scale * height + offset), scale * width, scale * height};
        DrawTexturePro(knight, src, dest, Vector2{}, 0.f, WHITE);
        DrawText("Welcome to Top Down Game!", 55.f, 45.f, 40, RED);
        DrawText("Control: A, S, W, D.", 55.f, 100.f, 30, RED);
        DrawText("Attack: Left click.", 55.f, 150.f, 30, RED);
        DrawText("Press spacebar to start.", 55.f, 200.f, 30, RED);
        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(knight);
    

}

void gameLogic(int windowWidth, int windowHeight, bool &reqWindowClose)
{
    if (reqWindowClose) return;
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

    while (kn.getAlive())
    {
        if (WindowShouldClose())
        {
            reqWindowClose = true;
            break;
        } 
        BeginDrawing();
        ClearBackground(WHITE);
        // draw map
        mapPos = Vector2Scale(kn.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);

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
        
        // check is all enemy was destroy
        bool isAllEnemyDie {true};
        for (auto enemy: enemies)
        {
            if (enemy->getAlive())
            {
                isAllEnemyDie = false;
                break;
            }
        }
        if (isAllEnemyDie)
        {
            DrawText("Victory", 55.f, 100.f, 30, RED);
            DrawText("Press spacebar to play again.", 55.f, 150.f, 30, RED);
            if (IsKeyDown(KEY_SPACE))
            {
                break;
            }
        }

        EndDrawing();
    }
    UnloadTexture(sword);
    UnloadCharacter(goblin, mushroom, skeleton, knight);
    UnloadTexture(map);
}

void gameOver(bool &reqWindowClose)
{
    if (reqWindowClose) return;
    Texture bg {LoadTexture("nature_tileset/Combined background - Blue.png")};
    float bg_x {};
    while (true)
    {
        if (IsKeyDown(KEY_SPACE)) break;
        if (WindowShouldClose())
        {
            reqWindowClose = true;
            break;
        }
              
        BeginDrawing();
        ClearBackground(WHITE);
        const float dT = GetFrameTime();
        bg_x += -40 * dT;
        // draw background
        if (bg_x < -bg.width *2)
        {
            bg_x = 0;
        }
        float bg_scale {0.8f};
        Vector2 bg1Pos {bg_x, 0};
        DrawTextureEx(bg, bg1Pos, 0.f, bg_scale, WHITE);
        Vector2 bg2Pos {bg_x + bg.width * bg_scale, 0};
        DrawTextureEx(bg, bg2Pos, 0.f, 2.f, WHITE);
        DrawText("Game Over!", 55.f, 45.f, 40, RED);
        DrawText("Press spacebar to play again.", 55.f, 100.f, 30, RED);
        EndDrawing();
    }
    UnloadTexture(bg);
}