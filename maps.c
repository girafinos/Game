#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "jogo.h"

void draw_map(Game *g){
    Map *map = &g->maps[g->curr_map];
    for(int i = 0; i < map->num_barriers; i++){
        DrawRectangleRec(map->barriers[i], SCREEN_COLOR);
    }

    if(map->door_locked)
        DrawRectangleRec(map->door, RED);
    else
        DrawRectangleRec(map->door, BLACK);

    if(map->prev_map != -1){
        DrawRectangleRec(map->prev_door, GREEN);
    }

    for(int i=0; i< map->num_enemies; i++){
        if(!map->enemies[i].draw_enemy) continue;
        DrawRectangleRec(map->enemies[i].pos, GREEN);
    }

    if(map->draw_special_item)
        DrawRectangleRec(map->special_item, PURPLE);
}

int barrier_collision(Map *map, Rectangle *target){
    for(int i = 0; i < map->num_barriers; i++){
        if(CheckCollisionRecs(*target, map->barriers[i])){
            return 1;
        }
    }
    return 0;
}

// Maps Setup
void map0_setup(Game *g){
    g->maps[0].num_barriers = 3;
    g->maps[0].barriers[0] = (Rectangle) {g->screenWidth/4, g->screenHeight/2 - (g->screenHeight/2-SCREEN_BORDER)/2, SCREEN_BORDER, g->screenHeight/2};
    g->maps[0].barriers[1] = (Rectangle) {g->screenWidth-(g->screenWidth/4)-SCREEN_BORDER, g->screenHeight/2 - (g->screenHeight/2-SCREEN_BORDER)/2, SCREEN_BORDER, g->screenHeight/2};
    g->maps[0].barriers[2] = (Rectangle) {g->screenWidth/2-(g->screenWidth/4), g->screenHeight/2, g->screenWidth/2, SCREEN_BORDER};
    g->maps[0].color = BLACK;
    g->maps[0].door = (Rectangle) {(g->screenWidth-(SCREEN_BORDER))/2-((200-SCREEN_BORDER)/2), 0, 200, SCREEN_BORDER};
    g->maps[0].num_enemies = 2;
    g->maps[0].door_locked = 1;

    for(int i=0; i< g->maps[0].num_enemies; i++){
        g->maps[0].enemies[i].pos = (Rectangle) { 2*g->screenWidth/3, 2*g->screenHeight/3, STD_SIZE_X, STD_SIZE_Y};
        g->maps[0].enemies[i].color = BLACK;
        g->maps[0].enemies[i].speed = 2;
        g->maps[0].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[0].enemies[i].draw_enemy = 1;
        g->maps[0].enemies[i].has_key = 0;
    }
    g->maps[0].enemies[0].has_key = 1;
    g->maps[0].special_item = (Rectangle) {g->screenWidth/2, 150, 12, 12};
    g->maps[0].draw_special_item = 1;
    g->maps[0].prev_map = -1;
    g->maps[0].next_map = 1;
}

void map1_setup(Game *g){
    g->maps[1].num_barriers = 2;
    g->maps[1].barriers[0] = (Rectangle) {3*g->screenWidth/4, 0, 2, 0.6 * g->screenHeight};
    g->maps[1].barriers[1] = (Rectangle) {g->screenWidth/4, 0.4*g->screenHeight, 2, g->screenHeight};
    g->maps[1].color = GRAY;
    g->maps[1].door = (Rectangle) {g->screenWidth-(SCREEN_BORDER+5), g->screenHeight/3, SCREEN_BORDER, 50};
    g->maps[1].prev_door = (Rectangle) {SCREEN_BORDER, g->screenHeight/3, 5, 50};
    g->maps[1].num_enemies = 3;
    g->maps[1].door_locked = 1;

    for(int i=0; i< g->maps[1].num_enemies; i++){
        g->maps[1].enemies[i].pos = (Rectangle) { 2*g->screenWidth/3, 2*g->screenHeight/3, STD_SIZE_X, STD_SIZE_Y};
        g->maps[1].enemies[i].color = BLACK;
        g->maps[1].enemies[i].speed = 6;
        g->maps[1].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[1].enemies[i].draw_enemy = 1;
        g->maps[1].enemies[i].has_key = 0;
    }
    g->maps[1].enemies[0].has_key = 1;
    g->maps[1].special_item = (Rectangle) {4*g->screenWidth/5, 20, 15, 15};
    g->maps[1].draw_special_item = 1;
    g->maps[1].prev_map = 0;
    g->maps[1].next_map = 2;
}

void map2_setup(Game *g){
    g->maps[2].num_barriers = 3;
    g->maps[2].barriers[0] = (Rectangle) {g->screenWidth/4, 0, 2, 0.6 * g->screenHeight};
    g->maps[2].barriers[1] = (Rectangle) {2*g->screenWidth/4, 0, 2, 0.6 * g->screenHeight};
    g->maps[2].barriers[2] = (Rectangle) {3*g->screenWidth/4, 0, 2, 0.6 * g->screenHeight};
    g->maps[2].color = GRAY;
    g->maps[2].door = (Rectangle) {g->screenWidth-(SCREEN_BORDER+5), g->screenHeight/3, SCREEN_BORDER, 50};
    g->maps[2].prev_door = (Rectangle) {SCREEN_BORDER, g->screenHeight/3, 5, 50};
    g->maps[2].num_enemies = 4;
    g->maps[2].door_locked = 1;

    for(int i=0; i< g->maps[2].num_enemies; i++){
        g->maps[2].enemies[i].pos = (Rectangle) { 2*g->screenWidth/3, 2*g->screenHeight/3, STD_SIZE_X, STD_SIZE_Y};
        g->maps[2].enemies[i].color = BLACK;
        g->maps[2].enemies[i].speed = 6;
        g->maps[2].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[2].enemies[i].draw_enemy = 1;
        g->maps[2].enemies[i].has_key = 0;
    }
    g->maps[2].enemies[0].has_key = 1;
    g->maps[2].special_item = (Rectangle) {4*g->screenWidth/5, 20, 15, 15};
    g->maps[2].draw_special_item = 1;
    g->maps[2].prev_map = 1;
    g->maps[2].next_map = 3;
}