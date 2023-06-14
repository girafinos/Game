#include "raylib.h"

#define SCREEN_COLOR (Color){109, 117, 229, 255}
#define STD_SIZE_X 30
#define STD_SIZE_Y 30
#define SCREEN_BORDER 16
#define MAX_SHOOTS 5

typedef struct Hero {
    Rectangle pos;
    Color color;
    int speed;
    int special;
    short int direc;
} Hero;

typedef struct Enemy {
    Rectangle pos;
    Color color;
    int speed;
    int direction;
    int draw_enemy;
    int has_key;
} Enemy;

typedef struct Map {
    Rectangle barriers[10];
    int num_barriers;
    Rectangle door;
    Rectangle prev_door;
    Color color;
    Enemy enemies[10];
    int num_enemies;
    Rectangle special_item;
    int draw_special_item;
    int door_locked;
    int next_map;
    int prev_map;
} Map;

typedef struct Shoot {
    Vector2 speed;
    bool active;
    Color color;
    Vector2 position;
    float radius;
    int lifeSpawn;
    int direc;
} Shoot;

typedef struct Game { 
    Map maps[10];
    int num_maps;
    int curr_map;
    Hero hero;
    Shoot shoot[5];
    Shoot enemies[1];
    int screenWidth;
    int screenHeight;
    int gameover;
} Game;

void InitGame(Game *g);         // Initialize game
void UpdateGame(Game *g);       // Update game (one frame)
void DrawGame(Game *g);         // Draw game (one frame)
void UpdateDrawFrame(Game *g);  // Update and Draw (one frame)

void draw_borders(Game *g);
void update_enemy_pos(Game *g, Enemy *e);
void update_hero_pos(Game *g);
void InitBullet(Game *g);
void updateBullet(Game *g);

void draw_map(Game *g);
int barrier_collision(Map *map, Rectangle *target);
void map0_setup(Game *g);
void map1_setup(Game *g);
void map2_setup(Game *g);