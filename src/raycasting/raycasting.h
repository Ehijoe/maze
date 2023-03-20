#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <Game.h>

void Raycast_Render(Game *game, float angle, int col);
void Raycast_DrawStrip(float distance, int col, Game *game);

#endif
