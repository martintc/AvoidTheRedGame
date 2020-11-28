#include <stdio.h>
#include "raylib.h"

void set_movement_zero (Vector2 *v);

int main () {

	char* game_over_message = "Game over, Press R to Reset or Q to Quit!";

	int width = 800;
	int height = 600;
	int fps = 30;

	int enemy_mov_x = -5;
	int enemy_mov_y = -5;

	int radius = 10;
	Vector2 player = {width/2, height/2};
	Vector2 enemy = {width-10, height-10};

	Vector2 mov_enemy = {enemy_mov_x,enemy_mov_y}; // movement for objects
	Vector2 mov_player = {10,10};

	InitWindow(width, height, "Avoid the Red!");
	SetTargetFPS(fps);

	while(!WindowShouldClose()) {

		// general game keys
		SetExitKey(KEY_Q); // quit the game by pressing 'q'

		if (IsKeyDown(KEY_R)) {
			player.x = width/2;
			player.y = height/2;
			enemy.x = width-10;
			enemy.y = height-10;
			mov_enemy.x = -5;
			mov_enemy.y = -5;
			mov_player.x = 10;
			mov_player.y = 10;
		}

		// enemy movement logic
		enemy.x = enemy.x + mov_enemy.x;
		enemy.y = enemy.y + mov_enemy.y;

		if (enemy.x >= (width - radius) || enemy.x <= radius)
			mov_enemy.x = mov_enemy.x * -1;
		if (enemy.y >= (height - radius) || enemy.y <= radius)
			mov_enemy.y = mov_enemy.y * -1;

		// player movement logic
		if(IsKeyDown(KEY_UP))
			player.y = player.y + (mov_player.y*-1);
		if(IsKeyDown(KEY_DOWN))
			player.y = player.y + mov_player.y;
		if(IsKeyDown(KEY_RIGHT))
			player.x = player.x + mov_player.x;
		if(IsKeyDown(KEY_LEFT))
			player.x = player.x + (mov_player.x*-1); 

		if (player.x == 0)
			player.x = width - radius;
		if (player.x == (width - radius))
			player.x = radius;
		if (player.y == 0)
			player.y = height - radius;
		if (player.y == (height - radius))
			player.y = radius;

		// collision logic
		if (CheckCollisionCircles(player, radius, enemy, radius)) {
			set_movement_zero(&mov_enemy);
			set_movement_zero(&mov_player);
			DrawText(game_over_message, 0, height/2, 36, WHITE);
		}

		BeginDrawing(); // {
			ClearBackground(BLACK);
			DrawCircleV(player, radius, GREEN);
			DrawCircleV(enemy, radius, RED);

		EndDrawing(); // }

	}

	CloseWindow();


}

void set_movement_zero (Vector2 *v) {
	v->x = 0;
	v->y = 0;
}