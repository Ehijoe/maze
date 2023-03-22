#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#include <Game.h>
#include <image.h>
#include <events.h>
#include <config.h>

#include "main.h"


/**
 * init_libraries - Initialize SDL and other third party libraries
 */
void init_libraries(void)
{
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n",
		       SDL_GetError());
		exit(1);
	}

	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n",
		       IMG_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		SDL_Log("Could not Initialize Mixer: %s", Mix_GetError());
	}
}


/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: List of arguments
 *
 * Return: Exit status
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	Game *game = NULL;
	SDL_Event e;
	bool quit = false;

	init_libraries();
	SDL_Log("Initialized Libraries");
	game = Game_create();
	SDL_Log("Created Game");

	Game_change_music(game, "assets/music/medieval.mp3");

	while ( quit == false )
	{
		int width, height;

		SDL_GetWindowSize(game->window, &width, &height);

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
			else
				event_handle(&e, game);
		}

		Game_draw(game);

		SDL_RenderPresent(game->renderer);
	}

	Game_close(game);

	return (0);
}
