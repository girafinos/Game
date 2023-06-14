#include "jogo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void InitBullet(Game *g){
    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        g->shoot[i].position = (Vector2){0, 0};
        g->shoot[i].speed = (Vector2) {0, 0};
        g->shoot[i].active = false;
        g->shoot[i].color = WHITE;
        g->shoot[i].radius = 4;
        g->shoot[i].lifeSpawn = 0;
    }
}

void updateBullet(Game *g){
    if(IsKeyPressed(KEY_SPACE) && g->hero.special)
    {   
        for(int i = 0; i < MAX_SHOOTS; i++)
        {
            if(!g->shoot[i].active)
            {
                g->shoot[i].position = (Vector2){g->hero.pos.x + 14, g->hero.pos.y + 14};
                g->shoot[i].active = true;   
                g->shoot[i].speed = (Vector2) {10, 10};
                g->shoot[i].direc = g->hero.direc;
                break;
            }
        }
    }     

    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        g->shoot[i].lifeSpawn++;
    }

    for (int i = 0; i < MAX_SHOOTS; i++) {           
        if (g->shoot[i].active) {
            switch (g->shoot[i].direc) { // Usa a direção armazenada do tiro
                case 1: // Direita
                    g->shoot[i].position.x += g->shoot[i].speed.x;
                    break;
                
                case 0: // Esquerda
                    g->shoot[i].position.x -= g->shoot[i].speed.x;
                    break;
                
                case 2: // Cima
                    g->shoot[i].position.y -= g->shoot[i].speed.y;
                    break;
                
                case 3: // Baixo
                    g->shoot[i].position.y += g->shoot[i].speed.y;
                    break;
            }

            if (g->shoot[i].lifeSpawn >= 9000) {
                g->shoot[i].position = (Vector2){g->hero.pos.x, g->hero.pos.y};
                g->shoot[i].speed = (Vector2){0, 0};
                g->shoot[i].lifeSpawn = 0;
                g->shoot[i].active = false;
            }

            if  (g->shoot[i].position.x > g->screenWidth + g->shoot[i].radius)
            {
                g->shoot[i].active = false;
                g->shoot[i].lifeSpawn = 0;
            }
            else if (g->shoot[i].position.x < 0 - g->shoot[i].radius)
            {
                g->shoot[i].active = false;
                g->shoot[i].lifeSpawn = 0;
            }
            if (g->shoot[i].position.y > g->screenHeight + g->shoot[i].radius)
            {
                g->shoot[i].active = false;
                g->shoot[i].lifeSpawn = 0;
            }
            else if (g->shoot[i].position.y < 0 - g->shoot[i].radius)
            {
                g->shoot[i].active = false;
                g->shoot[i].lifeSpawn = 0;
            }       
            for(int j = 0; j < g->maps[g->curr_map].num_barriers; j++){
                if(CheckCollisionCircleRec(g->shoot[i].position, g->shoot[i].radius, g->maps[g->curr_map].barriers[j]))
                {
                    g->shoot[i].active = false;
                    g->shoot[i].lifeSpawn = 0;
                }
            }   
        }
    }
}