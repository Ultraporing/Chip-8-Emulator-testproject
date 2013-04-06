#include <allegro5/allegro5.h>
#include "Chip8.h"
#include "ALGraphics.h"

Chip8 myChip8;

int main(int argc, char **argv)
{
	ALGraphics graphics(640);
	graphics.init();

	bool closeGame = false;

	while(!closeGame)
	{
		closeGame = graphics.HandleInput();
	}

	return 0;
}

bool setupGraphics()
{
	return true;
}