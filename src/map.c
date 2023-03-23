#include <map.h>
#include <stdlib.h>

#include <SDL2/SDL.h>


/**
 * Map_create - Load a map from a file
 * @map_filename: Path to map file
 *
 * Return: A pointer to the map struct
 */
Map *Map_create(char *map_filename)
{
	Map *map;
	unsigned int i, j, buf_size;
	SDL_RWops *map_file;
	char buffer[2048] = {0};

	map_file = SDL_RWFromFile(map_filename, "r");
	buf_size = SDL_RWread(map_file, buffer, sizeof(char), 2048);
	if (buf_size == 2048)
	{
		SDL_Log("Map file too big.");
		return (NULL);
	}
	SDL_RWclose(map_file);
	map = malloc(sizeof(map));
	if (map == NULL)
		return (NULL);
	Map_setSize(buffer, buf_size, map);
	map->cells = malloc(sizeof(Cell *) * map->h);
	if (map->cells == NULL)
	{
		free(map);
		return (NULL);
	}
	for (i = 0; i < map->h; i++)
	{
		map->cells[i] = malloc(sizeof(Cell) * map->w);
		if (map->cells[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(map->cells[i]);
			free(map->cells);
			free(map);
		}
	}
	Map_initialize(buffer, map);
	return (map);
}


/**
 * Map_setSize - Set the size of the map
 * @buffer: Buffer with the map info
 * @map: Map to set the size of
 */
void Map_setSize(char *buffer, unsigned int buf_size, Map *map)
{
	unsigned int i;

	for (i = 0; i < buf_size; i++)
	{
		if (buffer[i] == '\n')
			buffer[i] = '\0';
	}
	map->w = atoi(buffer);
	for (i = 0; buffer[i] != '\0'; i++)
		continue;
	map->h = atoi(&buffer[i + 1]);
}


/**
 * Map_initialize - Initialize a map according to a file
 * @buffer: Buffer holding file contents
 * @map: Map to initialize
 */
void Map_initialize(char *buffer, Map *map)
{
	unsigned int i, j, k;

	k = 0;
	for (i = 0; i < 2; i++)
	{
		for (; buffer[k] != '\0'; k++)
			continue;
		k++;
	}
	for (i = 0; i < map->h; i++)
	{
		for (j = 0; j < map->w; j++)
		{
			if (buffer[k] == '#')
				map->cells[i][j] = CELL_WALL;
			else
				map->cells[i][j] = CELL_NONE;
			k++;
		}
		k++;
	}
}


/**
 * Map_free - Free the memory used by a map
 * @map: Map to delete
 */
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
