#include <allegro5/allegro5.h>
#include "Chip8.h"
#include "ALGraphics.h"



int main(int argc, char **argv)
{
	Chip8 myChip8;
	ALGraphics graphics(10);
	graphics.init();
	myChip8.initialize();

	bool closeGame = false;

	if (argc > 1)
	{
		myChip8.loadApplication(argv[1]);
	}
	

	while(!closeGame)
	{
		myChip8.emulateCycle();
		closeGame = graphics.HandleInput(myChip8);
	}

	return 0;
}