#include <map.h>
#include <stdlib.h>

#include <SDL2/SDL.h>


Map *Map_create(void)
{
	Map *map;
	unsigned int i, j;

	map = malloc(sizeof(map));
	if (map == NULL)
		return (NULL);

	map->w = 6;
	map->h = 6;
	map->cells = NULL;

	map->cells = malloc(sizeof(Uint8 *) * map->h);
	if (map->cells == NULL)
	{
		free(map);
		return (NULL);
	}
	for (i = 0; i < map->h; i++)
	{
		map->cells[i] = malloc(sizeof(Uint8) * map->w);
		if (map->cells[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(map->cells[i]);
			free(map->cells);
			free(map);
		}
	}

	/* Initialize Test map */
	for (i = 0; i < map->h; i++)
	{
		for (j = 0; j < map->w; j++)
		{
			if (i == 0 || i == map->h - 1 || j == 0 || j == map->w - 1)
				map->cells[i][j] = CELL_WALL;
			else
				map->cells[i][j] = CELL_NONE;
		}
	}

	SDL_Log("Created map");

	return (map);
}


void Map_free(Map *map)
{
	unsigned int i;

	if (map == NULL)
		return;

	if (map->cells != NULL)
	{
		for (i = 0; i < map->h; i++)
		{
			if (map->cells[i] != NULL)
				free(map->cells[i]);
		}
		free(map->cells);
	}
	free(map);
}
