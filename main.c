#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "jogo.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Game game;
    game.screenWidth = 800;
    game.screenHeight = 600;

    InitWindow(game.screenWidth, game.screenHeight, "Aedsinho's quest");

    SetTargetFPS(60);
    
    InitGame(&game);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame(&game);
        DrawFPS(10,10);
        if(game.gameover) break;
    }
    while(!IsKeyDown(KEY_ENTER)){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("GAME OVER", GetScreenWidth()/2 - MeasureText("GAME OVER", 20)/2, GetScreenHeight()/2 - 50, 20, BLACK);
        EndDrawing();
        sleep(1); //timer pra fechar a janela do jogo//
        CloseWindow(); //fecha a janela dps do jogo//
        
    }
    return 0;
}

