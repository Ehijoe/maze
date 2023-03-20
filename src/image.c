#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

#include <Game.h>


/**
 * load_image - Load an image as a texture
 * @image: Path to image file
 * @game: Game to load texture into
 *
 * Return: A pointer to the texture
 */
SDL_Texture *load_image(char *image, Game *game)
{
	SDL_Texture *texture = NULL;
	SDL_Texture **textures = NULL;

	texture = IMG_LoadTexture(game->renderer, image);
	if (texture == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", image,
		       SDL_GetError());
		Game_close(game);
		exit(1);
	}

	textures = realloc(game->textures,
			   sizeof(SDL_Texture *) * game->textureCount);
	if (textures == NULL)
	{
		perror("load_image");
		SDL_DestroyTexture(texture);
		Game_close(game);
		exit(1);
	}

	textures[game->textureCount] = texture;
	game->textureCount++;
	game->textures = textures;

	return (texture);
}
