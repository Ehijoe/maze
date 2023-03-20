#ifndef RAYCASTING_MATH_H
#define RAYCASTING_MATH_H

#include <map.h>
#include <characters.h>

int check_wall_vertical(Map *map, float x, float y, float angle);
int check_wall_horizontal(Map *map, float x, float y, float angle);
float calculate_distance(float x, float y, Character *player);
void get_ray_distance(Map *map, Character *player,
		      float *x, float *y, float angle);

#endif
