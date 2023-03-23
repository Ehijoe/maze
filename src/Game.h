#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <characters.h>
#include <map.h>

/**
 * struct Game - Stores all game data
 * @window: Pointer to the SDL window
 * @screenSurface: Pointer to the SDL window's surface
 * @surfaces: Array of allocated surfaces
 * @surfaceCount: Number of allocated surfaces
 * @music: Pointer to the music
 */
typedef struct Game
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture **textures;
	int textureCount;
	Mix_Music *music;
	Character *player;
	Map *map;
} Game;

Game *Game_create(char *map_file);
void Game_change_music(Game *game, char *music_file);
void Game_draw(Game *game);
void Game_close(Game *game);

#endif
