#include "Prop.h"
#include "raymath.h"
 Prop::Prop(Vector2 pos,Texture2D tex):
        worldpos(pos),
        texture(tex)
 {

 }
 void Prop :: Render(Vector2 knightPos)
 {
    Vector2 screenPos{ Vector2Subtract(worldpos,knightPos) };
    DrawTextureEx(texture,screenPos, 0.f,scale, WHITE);
 }
 Rectangle Prop:: getCollisionRec(Vector2 knightPos)
 {
    Vector2 screenPos{ Vector2Subtract(worldpos, knightPos) };
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height *scale
    };
 }