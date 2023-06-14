#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "jogo.h"

#define SCREEN_COLOR (Color){109, 117, 229, 255}
#define STD_SIZE_X 30
#define STD_SIZE_Y 30
#define SCREEN_BORDER 16
#define MAX_SHOOTS 5

void InitGame(Game *g){

    InitBullet(g);
    g->curr_map = 0;
    g->num_maps = 10;
    g->hero.pos = (Rectangle) { 150, 300, STD_SIZE_X, STD_SIZE_Y};
    g->hero.color = PINK;
    g->hero.speed = 5;
    g->hero.special = 0;
    g->gameover = 0;
    map0_setup(g);
    map1_setup(g);
    map2_setup(g);
}
 
// Update game (one frame)
void UpdateGame(Game *g)
{
    update_hero_pos(g);
    updateBullet(g);

    Map *map = &g->maps[g->curr_map];
        for(int i; i < map->num_enemies; i++){
            if(!map->enemies[i].draw_enemy) continue;
            update_enemy_pos(g, &map->enemies[i]);
            if(!CheckCollisionRecs(g->hero.pos, map->enemies[i].pos))
                continue;
            
            if(g->hero.special){
                map->enemies[i].draw_enemy = 0;
                
            }
            g->gameover = 1;
        }
    
    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        if(g->shoot[i].active){
            for(int j; j < map->num_enemies; j++){
                if (CheckCollisionCircleRec(g->shoot[i].position, g->shoot[i].radius, map->enemies[j].pos) && map->enemies[j].draw_enemy != 0)
                {
                    map->enemies[j].draw_enemy = 0;
                    g->shoot[i].active = false;
                    g->shoot[i].lifeSpawn = 0;
                    if(map->enemies[i].has_key) {
                    map->door_locked = 0;
                }
                }     
            }
        }
    }

    if(CheckCollisionRecs(g->hero.pos, map->special_item) && map->draw_special_item){
        g->hero.special = 1;
        map->draw_special_item = 0;
    }

    if(CheckCollisionRecs(g->hero.pos, map->door) && !map->door_locked){
        g->curr_map = map->next_map;
        g->hero.pos = (Rectangle) { 50, 200, STD_SIZE_X, STD_SIZE_Y};
        g->hero.special = 0;
    }

    if(map->prev_map != -1 && CheckCollisionRecs(g->hero.pos, map->prev_door)){
        g->curr_map = map->prev_map;
        g->hero.pos = (Rectangle) { g->screenWidth-50, g->screenHeight/3, STD_SIZE_X, STD_SIZE_Y};
        g->hero.special = 0;
    }

}

// Draw game (one frame)
void DrawGame(Game *g)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, g->screenWidth, g->screenHeight, BLACK);
    draw_borders(g);
    draw_map(g);

    DrawRectangleRec(g->hero.pos, g->hero.color);
    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        if(g->shoot[i].active)
        {
            DrawCircleV(g->shoot[i].position, g->shoot[i].radius, WHITE);
        }
    } 

    EndDrawing();
}

// Update and Draw (one frame)
void UpdateDrawFrame(Game *g)
{
    UpdateGame(g);
    DrawGame(g);
}

void draw_borders(Game *g)
{
    DrawRectangle(0, 0, SCREEN_BORDER, g->screenHeight, SCREEN_COLOR);
    DrawRectangle(0, 0, g->screenWidth, SCREEN_BORDER, SCREEN_COLOR);
    DrawRectangle(g->screenWidth-SCREEN_BORDER, 0, g->screenWidth, g->screenHeight, SCREEN_COLOR);
    DrawRectangle(0, g->screenHeight-SCREEN_BORDER, g->screenWidth, g->screenHeight, SCREEN_COLOR);
}

void update_hero_pos(Game *g){

    Hero *h = &g->hero;
    Map *m = &g->maps[g->curr_map];

    if(IsKeyDown(KEY_A) && IsKeyDown(KEY_W)) {
        if((h->pos.x > SCREEN_BORDER) && (h->pos.y > SCREEN_BORDER))
        {
            h->pos.x -= h->speed; 
            h->pos.y -= h->speed;
        }
        if(barrier_collision(m, &h->pos)) 
        {
            h->pos.x += h->speed;
            h->pos.y += h->speed;
        }
    } else if(IsKeyDown(KEY_D) && IsKeyDown(KEY_W)) {
        if((h->pos.x + h->pos.width < g->screenWidth - SCREEN_BORDER) && (h->pos.y > SCREEN_BORDER))
        {
            h->pos.x += h->speed;
            h->pos.y -= h->speed/2;
        }
        if(barrier_collision(m, &h->pos)) 
        {
            h->pos.x -= h->speed;
            h->pos.y -= h->speed/2;
        }

    } else if(IsKeyDown(KEY_A) && IsKeyDown(KEY_S)) {
        if((h->pos.x > SCREEN_BORDER) && (h->pos.y + h->pos.height < g->screenHeight - SCREEN_BORDER))
        {
            h->pos.x -= h->speed;
            h->pos.y += h->speed/2;
        }
        if(barrier_collision(m, &h->pos))
        {
            h->pos.x += h->speed;
            h->pos.y -= h->speed/2;
        }

    } else if(IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) {
        if((h->pos.x + h->pos.width < g->screenWidth - SCREEN_BORDER) && (h->pos.y + h->pos.height < g->screenHeight - SCREEN_BORDER))
            {
                h->pos.x += h->speed;
                h->pos.y += h->speed/2;
            }
            if(barrier_collision(m, &h->pos))
            {
                h->pos.x -= h->speed;
                h->pos.y -= h->speed/2;
            }

    } else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        h->direc = 0;
        if(h->pos.x > SCREEN_BORDER)
            h->pos.x -= h->speed; 
        if(barrier_collision(m, &h->pos)) h->pos.x += h->speed;

    } else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        h->direc = 1;
        if(h->pos.x + h->pos.width < g->screenWidth - SCREEN_BORDER)
            h->pos.x += h->speed;
        if(barrier_collision(m, &h->pos)) h->pos.x -= h->speed;

    } else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        h->direc = 2;
        if(h->pos.y > SCREEN_BORDER)
            h->pos.y -= h->speed;
        if(barrier_collision(m, &h->pos)) h->pos.y += h->speed;

    } else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        h->direc = 3;
        if(h->pos.y + h->pos.height < g->screenHeight - SCREEN_BORDER)
            h->pos.y += h->speed;
        if(barrier_collision(m, &h->pos)) h->pos.y -= h->speed;
    } 
}








