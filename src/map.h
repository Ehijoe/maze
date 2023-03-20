#ifndef MAP_H
#define MAP_H

typedef enum
{
	CELL_WALL,
	CELL_NONE,
	CELL_GOAL,
	CELL_START
} Cell;

typedef struct Map
{
	unsigned int w;
	unsigned int h;
	Cell **cells;
} Map;

Map *Map_create(void);
void Map_free(Map *map);

#endif
