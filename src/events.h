#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>

#include <Game.h>

void event_handle(SDL_Event *e, Game *game);
void event_handle_keyboard(SDL_Event *e, Game *game);

#endif
