#include "raylib.h"
#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter :: BaseCharacter()
{
    
}
void BaseCharacter:: Undomovement()
{
        worldpos=worldPoslastFrame;
}
Rectangle BaseCharacter :: getCollisionRec()
  {
    return Rectangle{
        getScreenpos().x,
        getScreenpos().y,
        width * scale,
        height * scale
    };
  }
  void BaseCharacter :: tick(float deltaTime)
  {
    worldPoslastFrame = worldpos;
     runningtime += deltaTime;
    if (runningtime >= updatetime)
    {
        frame++;
        runningtime = 0.f;
        if (frame > maxframes)
            frame = 0;
    }

       if (Vector2Length(velocity) != 0.0)
    {
        worldpos = Vector2Add(worldpos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? righleft = -1.f : righleft = 1.f;
        texture = run;
    }
    else
        texture = idle;

    velocity = {};

    // loading character
    Rectangle source{frame * width , 0.f, righleft * width, height};
    Rectangle dest{getScreenpos().x, getScreenpos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
  }