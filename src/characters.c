#include <characters.h>

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>


Character *Character_create(void)
{
	Character *player;

	SDL_Log("Creating player");
	player = malloc(sizeof(Character));
	if (player == NULL)
	{
		perror("Character_create");
		exit(1);
	}
	player->x = 5.0;
	player->y = 5.0;
	player->direction = 45.0;
	SDL_Log("Created Player");

	return (player);
}
