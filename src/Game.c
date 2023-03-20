#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include <Game.h>
#include <raycasting.h>
#include <config.h>

/**
 * Game_create - Create a game and it's window
 *
 * Return: A pointer to the game
 */
Game *Game_create(void)
{
	Game *game;

	game = malloc(sizeof(Game));
	if (game == NULL)
	{
		perror("Game_create");
		exit(1);
	}

	game->music = NULL;
	game->textures = NULL;
	game->textureCount = 0;
	game->renderer = NULL;

	game->window = SDL_CreateWindow(GAME_NAME,
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					DEFAULT_SCREEN_WIDTH,
					DEFAULT_SCREEN_HEIGHT,
					SDL_WINDOW_SHOWN);
	if (game->window == NULL)
	{
		SDL_Log("Could not create window: %s", SDL_GetError());
		exit(1);
	}
	game->renderer = SDL_CreateRenderer(game->window, -1,
					    SDL_RENDERER_ACCELERATED);
	if (game->renderer == NULL)
	{
		SDL_Log("Could not create renderer: %s", SDL_GetError());
		Game_close(game);
		exit(1);
	}
	game->map = Map_create();
	game->player = Character_create();
	SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND);
	return (game);
}


/**
 * Game_change_music - Load and play a song
 * @game: Pointer to the Game object
 * @music_file: Name of the music file to load
 */
void Game_change_music(Game *game, char *music_file)
{
	Mix_Music *music = NULL;

	if (game->music != NULL)
	{
		Mix_FreeMusic(game->music);
		game->music = NULL;
	}
	music = Mix_LoadMUS(music_file);
	if (music == NULL)
	{
		SDL_Log("Could not load music file '%s': %s",
			music_file, Mix_GetError());
		return;
	}
	SDL_Log("Loaded Music");
	Mix_FadeInMusic(music, -1, 500);
	SDL_Log("Playing Music");
}


/**
 * Game_draw - Draw the map as seen by the player
 * @game: Game object
 */
void Game_draw(Game *game)
{
	float angle, angle_step;
	Character *player = game->player;
	int col;

	SDL_Log("Player position\tx: %f\ty: %f", player->x, player->y);
	angle = player->direction + (FOV_ANGLE / 2.0);
	angle_step = FOV_ANGLE / ((double) DEFAULT_SCREEN_WIDTH);
	SDL_SetRenderDrawColor(game->renderer, 0xAA, 0xAA, 0xAA, 0xFF);
	for (col = 0; col <= 800; angle -= angle_step, col++)
	{
	        Raycast_Render(game, angle, col);
	}
}


/**
 * Game_close - Close game resources
 * @game: Game to close
 */
void Game_close(Game *game)
{
	if (game == NULL)
		return;

	if (game->textureCount > 0 && game->textures != NULL)
	{
		int i;

		for (i = game->textureCount - 1; i >=0; i--)
		{
			if (game->textures[i] != NULL)
				SDL_DestroyTexture(game->textures[i]);
		}
	}

	Map_free(game->map);
	free(game->player);

	if (game->renderer != NULL)
	{
		SDL_DestroyRenderer(game->renderer);
	}

	if (game->music != NULL)
	{
		Mix_FreeMusic(game->music);
	}

	if (game->window != NULL)
	{
		SDL_DestroyWindow(game->window);
	}
	free(game);

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
