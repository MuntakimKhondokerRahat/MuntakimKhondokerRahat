#include <bits/stdc++.h>
using namespace std;
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "prop.h"
#include "Enemy.h"
int main()
{
    const int windowWidth{768};
    const int windowHeight{768};
    InitWindow(windowWidth, windowHeight, "Final Project");
    InitAudioDevice();
    Sound swordSound = LoadSound("audio/sword.wav");
    Music bgMusic = LoadMusicStream("audio/bgmusic.mp3");

    PlayMusicStream(bgMusic);

    Texture2D map = LoadTexture("nt/map.png");
    Vector2 mappos{0.0, 0.0};
    const float mapscale{4.0};

    Character knight{windowWidth, windowHeight};
   Prop props[25]{
    // Sign at the starting area — unchanged
    Prop{Vector2{300.f, 120.f}, LoadTexture("nt/sign.png")},
    // Rocks
    Prop{Vector2{650.f, 300.f}, LoadTexture("nt/Rock.png")},
    Prop{Vector2{350.f, 500.f}, LoadTexture("nt/Rock.png")},
    Prop{Vector2{923.f, 440.f}, LoadTexture("nt/Rock.png")},
    Prop{Vector2{1100.f, 800.f}, LoadTexture("nt/Rock.png")},
    Prop{Vector2{1500.f, 350.f}, LoadTexture("nt/Rock.png")},
    Prop{Vector2{800.f, 1200.f}, LoadTexture("nt/Rock.png")},
    Prop{Vector2{1900.f, 650.f}, LoadTexture("nt/Rock.png")},
    Prop{Vector2{2400.f, 1100.f}, LoadTexture("nt/Rock.png")},
    // Logs
    Prop{Vector2{430.f, 250.f}, LoadTexture("nt/Log.png")},
    Prop{Vector2{672.f, 610.f}, LoadTexture("nt/Log.png")},
    Prop{Vector2{1200.f, 500.f}, LoadTexture("nt/Log.png")},
    Prop{Vector2{500.f, 900.f}, LoadTexture("nt/Log.png")},
    Prop{Vector2{1400.f, 1000.f}, LoadTexture("nt/Log.png")},
    Prop{Vector2{1000.f, 1400.f}, LoadTexture("nt/Log.png")},
    Prop{Vector2{2100.f, 1700.f}, LoadTexture("nt/Log.png")},
    Prop{Vector2{2600.f, 2200.f}, LoadTexture("nt/Log.png")},
    // Bushes
    Prop{Vector2{250.f, 750.f}, LoadTexture("nt/Bush.png")},
    Prop{Vector2{750.f, 650.f}, LoadTexture("nt/Bush.png")},
    Prop{Vector2{1650.f, 800.f}, LoadTexture("nt/Bush.png")},
    Prop{Vector2{2000.f, 1200.f}, LoadTexture("nt/Bush.png")},
    Prop{Vector2{600.f, 1800.f}, LoadTexture("nt/Bush.png")},
    Prop{Vector2{1300.f, 2100.f}, LoadTexture("nt/Bush.png")},
    Prop{Vector2{2300.f, 2400.f}, LoadTexture("nt/Bush.png")},
    Prop{Vector2{1920.f, 1500.f}, LoadTexture("nt/Bush.png")}
};
    vector<Enemy> enemies;
    Texture2D goblinIdle =
        LoadTexture("characters/goblin_idle_spritesheet.png");

    Texture2D goblinRun =
        LoadTexture("characters/goblin_run_spritesheet.png");
    Texture2D slimeIdle =
        LoadTexture("characters/slime_idle_spritesheet.png");

    Texture2D slimeRun =
        LoadTexture("characters/slime_run_spritesheet.png");

    enemies.emplace_back(
        Vector2{800.f, 300.f},
        goblinIdle,
        goblinRun);

    enemies.back().setTarget(&knight);

    enemies.emplace_back(Vector2{500.f, 700.f}, goblinIdle, goblinRun);

    enemies.back().setTarget(&knight);
    float spawnTimer = 0.f;
    int score = 0;
    bool gameStarted = false;
   bool gamePaused = false;
    SetTargetFPS(80);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        UpdateMusicStream(bgMusic);
        if (!gameStarted)
        {
            DrawText("MY ADVENTURE GAME", 84, 84, 50, DARKGREEN);

            DrawText("Press SPACE to Start", 84, 184, 50, DARKBLUE);

            if (IsKeyPressed(KEY_SPACE))
            {
                gameStarted = true;
            }

            EndDrawing();
            continue;
        }
        if (IsKeyPressed(KEY_P))
        {
             gamePaused = !gamePaused;
        }
        if (gamePaused)
            {
                 DrawRectangle(0, 0, windowWidth, windowHeight,
                              Fade(BLACK, 0.6f));
                const char *pauseText = "GAME PAUSED";

                DrawText(pauseText,(windowWidth - MeasureText(pauseText, 40)) / 2, 300, 40, WHITE);

                DrawText("Press P to Resume",220, 380, 30, YELLOW);

                EndDrawing();
                    continue;
                }

        mappos = Vector2Scale(knight.getworldpos(), -1.f);

        // loading map
        DrawTextureEx(map, mappos, 0.0, mapscale, WHITE);

        // draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getworldpos());
        }

        if (!knight.getAlive())
        {
            // GAME OVER
            const char *title = "GAME OVER";
            DrawText(title,
                     (windowWidth - MeasureText(title, 40)) / 2,
                     250, 40, RED);

            // Final score
            const char *scoreText =
                TextFormat("Final Score: %i", score);

            DrawText(scoreText,
                     (windowWidth - MeasureText(scoreText, 30)) / 2,
                     320, 30, ORANGE);

            // Retry message
            const char *retryText = "Press SPACE to Try Again";

            DrawText(retryText,
                     (windowWidth - MeasureText(retryText, 25)) / 2,
                     390, 25, WHITE);
            if (IsKeyPressed(KEY_SPACE))
            {
                gameStarted = true;

                knight.Reset();
                score = 0;
                spawnTimer = 0.f;
                enemies.clear();

                enemies.emplace_back(Vector2{800.f, 300.f}, goblinIdle, goblinRun);
                enemies.back().setTarget(&knight);

                enemies.emplace_back(Vector2{500.f, 700.f}, goblinIdle, goblinRun);
                enemies.back().setTarget(&knight);
            }

            EndDrawing();
            continue;
        }
        knight.tick(GetFrameTime());

        // checking map bounds
        float mapWidth = map.width * mapscale;
        float mapHeight = map.height * mapscale;

        if (knight.getworldpos().x < 0.f ||
            knight.getworldpos().y < 0.f ||
            knight.getworldpos().x + windowWidth > mapWidth ||
            knight.getworldpos().y + windowHeight > mapHeight)
        {
            knight.Undomovement();
        }

        // prop collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getworldpos()), knight.getCollisionRec()))
            {
                knight.Undomovement();
            }
        }
        // ENEMY ALIVE
        for (auto &enemy : enemies)
        {
            if (enemy.getAlive())
            {
                enemy.tick(GetFrameTime());
            }
        }
        // ATTACK
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            PlaySound(swordSound);
            for (auto &enemy : enemies)
            {
                if (enemy.getAlive() &&CheckCollisionRecs(enemy.getCollisionRec(),knight.getWeaponCollisonRec()))
                {
                    enemy.setAlive(false);
                    score++;
                }
            }
        }
        spawnTimer += GetFrameTime();

        if (spawnTimer >= 2.f)
        {
            spawnTimer = 0.f;

            for (int i = 0; i < enemies.size(); i++)
            {
                if (!enemies[i].getAlive())
                {
                    enemies.erase(enemies.begin() + i);
                    i--;
                }
            }

            float x = GetRandomValue(100, map.width * mapscale - 100);
            float y = GetRandomValue(100, map.height * mapscale - 100);
            int type = GetRandomValue(1, 2);
            if (type == 1)
            {
                enemies.emplace_back(
                    Vector2{x, y},
                    goblinIdle,
                    goblinRun);
            }
            else
            {
                enemies.emplace_back(
                    Vector2{x, y},
                    slimeIdle,
                    slimeRun);
            }

            enemies.back().setTarget(&knight);
        }
        DrawText(TextFormat("Health: %.0f", knight.getHealth()), 280, 20, 35, RED);
        DrawText(TextFormat("Score: %i", score), 280, 60, 35, ORANGE);

        EndDrawing();
    }
    UnloadSound(swordSound);
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    CloseWindow();
}