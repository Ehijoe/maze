#include <raycasting.h>
#include <raycasting_math.h>
#include <map.h>
#include <characters.h>
#include <Game.h>
#include <math.h>

#include <SDL2/SDL.h>


/**
 * Raycast_Render - Cast a ray from player and render on the screen
 * @game: Game object
 * @angle: Angle at which to project the ray
 * @col: Column to render
 */
void Raycast_Render(Game *game, float angle, int col)
{
	float x, y, distance, diff_angle;
	Character *player;
	Map *map;

	player = game->player;
	if (angle > 360.0)
		angle -= 360.0;
	if (angle < 0.0)
		angle += 360.0;
	diff_angle = angle - player->direction;
	angle *= M_PI / 180.0;
	diff_angle *= M_PI / 180.0;
	map = game->map;
	get_ray_distance(map, player, &x, &y, angle);
	distance = (x > y) ? y : x;
	distance *= fabs(cos(diff_angle));
	SDL_Log("Angle: %f\tDistance: %f", (angle * 180.0 / M_PI), distance);
	if (distance < 6.95)
	{
		SDL_Log("X: %f\tY: %f", x, y);
		trace_ray_distance(map, player, &x, &y, angle);
		SDL_Log("X: %f\tY: %f", x, y);
	}
	Raycast_DrawStrip(distance, col, game);
}


/**
 * Raycast_DrawWall - Draw a strip of a wall a distance from the player
 * @distance: Distance of the wall from the player
 * @col: Column to draw
 * @game: Game to draw on
 */
void Raycast_DrawStrip(float distance, int col, Game *game)
{
	int height;

	height = round(692.8 / distance);
	SDL_RenderDrawLine(game->renderer, col, (300 + (height / 2)),
			   col, (300 - (height / 2)));
}
