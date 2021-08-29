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