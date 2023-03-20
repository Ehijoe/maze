#ifndef PLAYER_H
#define PLAYER_H

typedef struct Character
{
	float x;
	float y;
	float direction;
} Character;

Character *Character_create(void);

#endif
