#include <events.h>
#include <Game.h>
#include <characters.h>

#include <SDL2/SDL.h>
#include <math.h>


/**
 * event_handle - Handle an SDL_event
 * @e: Event
 * @game: The game to work on
 */
void event_handle(SDL_Event *e, Game *game)
{
	switch (e->type)
	{
	case SDL_KEYDOWN:
		event_handle_keyboard(e, game);
		break;
	default:
		break;
	}
}


/**
 * event_handle - Handle an SDL_event
 * @e: Event
 * @game: The game to work on
 */
void event_handle_keyboard(SDL_Event *e, Game *game)
{
	Character *player;

	player = game->player;
	if (e->key.keysym.sym == SDLK_f)
	{
		if (SDL_SetWindowFullscreen(game->window,
					     SDL_WINDOW_FULLSCREEN_DESKTOP))
		{
			SDL_Log("Could not Fullscreen: %s", SDL_GetError());
		}
	}
	else if (e->key.keysym.sym == SDLK_g)
	{
		if (SDL_SetWindowFullscreen(game->window, 0))
		{
			SDL_Log("Could not Fullscreen: %s", SDL_GetError());
		}
	}
	else if (e->key.keysym.sym == SDLK_a)
	{
		game->player->direction += 5.0;
	}
	else if (e->key.keysym.sym == SDLK_d)
	{
		game->player->direction -= 5.0;
	}
	else if (e->key.keysym.sym == SDLK_w)
	{
		player->y -= 0.1 * sin(player->direction * M_PI / 180.0);
		player->x += 0.1 * cos(player->direction * M_PI / 180.0);
	}
	else if (e->key.keysym.sym == SDLK_s)
	{
		player->y += 0.1 * sin(player->direction * M_PI / 180.0);
		player->x -= 0.1 * cos(player->direction * M_PI / 180.0);
	}
}
