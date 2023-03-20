#include <math.h>
#include <SDL2/SDL.h>

#include <raycasting_math.h>
#include <map.h>
#include <characters.h>


/**
 * check_wall_vertical - Check if a point is on a horizontal wall
 * @map: Map to check
 * @x: X coordinate of point
 * @y: Y coordinate of point
 * @angle: Angle of ray
 */
int check_wall_vertical(Map *map, float x, float y, float angle)
{
	unsigned int x_idx, y_idx;

	y_idx = (unsigned int) floor(y);
	if (angle < M_PI * 0.5 || angle > M_PI * 1.5)
	{
		x_idx = (unsigned int) round(x);
	}
	else
	{
		x_idx = (unsigned int) round(x - 1.0);
	}
	if (map->w <= x_idx || map->h <= y_idx)
		return (1);
	return (map->cells[y_idx][x_idx] == CELL_WALL);
}


/**
 * check_wall_horizontal - Check if a point is on a horizontal wall
 * @map: Map to check
 * @x: X coordinate of point
 * @y: Y coordinate of point
 * @angle: Angle of ray
 */
int check_wall_horizontal(Map *map, float x, float y, float angle)
{
	unsigned int x_idx, y_idx;

	x_idx = (unsigned int) floor(x);
	if (angle > M_PI)
	{
		y_idx = (unsigned int) round(y);
	}
	else
	{
		y_idx = (unsigned int) round(y - 1.0);
	}
	if (map->w <= x_idx || map->h <= y_idx)
		return (1);
	return (map->cells[y_idx][x_idx] == CELL_WALL);
}


/**
 * calculate_distance - Find the distance of the player from a point
 * @x: X coordinate of point
 * @y: Y coordinate of point
 * @player: Pointer to the player
 *
 * Return: The distance between the player and the point
 */
float calculate_distance(float x, float y, Character *player)
{
	float delta_x, delta_y;

	delta_x = x - player->x;
	delta_y = y - player->y;
	delta_x *= delta_x;
	delta_y *= delta_y;
	return sqrt(delta_x + delta_y);
}


/**
 * get_ray_distance - Get the point where a ray strikes a wall
 * @map: Map
 * @player: The observer
 * @x: Pointer to store the x position
 * @y: Pointer to store the y position
 * @angle: Direction of the ray
 */
void get_ray_distance(Map *map, Character *player,
		      float *x, float *y, float angle)
{
	/* y_delta is the slope and x_delta is its inverse */
	float x_delta, y_delta;
	float x_pos, y_pos;
	float x_step = -1.0;
	float y_step = -1.0;

	y_delta = tanf(angle);
	x_delta = 1.0 / y_delta;
	if (angle > M_PI)
	{
		x_delta *= -1.0;
		y_step = 1.0;
	}
	if (angle < (M_PI * 0.5) || angle > (M_PI * 1.5))
	{
		y_delta *= -1.0;
		x_step = 1.0;
	}

	y_pos = floor(player->y);
	x_pos = player->x + (x_delta * (y_pos - player->y));
	while (!check_wall_horizontal(map, x_pos, y_pos, angle))
	{
		x_pos += x_delta;
		y_pos += y_step;
	}
	*x = calculate_distance(x_pos, y_pos, player);

	x_pos = floor(player->x);
	y_pos = player->y + (y_delta * (x_pos - player->x));
	while (!check_wall_vertical(map, x_pos, y_pos, angle))
	{
		x_pos += x_step;
		y_pos += y_delta;
	}
	*y = calculate_distance(x_pos, y_pos, player);
}
