#include "Enemy.h"
#include "raymath.h"
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) 
    {
        if(!getAlive()) return;
        worldpos=pos;
     texture = idle_texture;
     idle = idle_texture;
     run =run_texture;
      width=texture.width/maxframes;
      height =texture.height;
      speed = 3.f;
    }
    void Enemy :: tick(float deltaTime)
    {
        if(!getAlive()) return; 
        //get toTarget
        velocity = Vector2Subtract(target->getScreenpos(),getScreenpos());
        if(Vector2Length(velocity) < radius ) velocity={};
        BaseCharacter:: tick(deltaTime);

        if(CheckCollisionRecs( target->getCollisionRec(), getCollisionRec()))
        {
           target ->takeDamage(damagePersec * deltaTime);
        }
    }
    Vector2 Enemy :: getScreenpos()
    {
        return  Vector2Subtract(worldpos,target-> getworldpos());
    }
  