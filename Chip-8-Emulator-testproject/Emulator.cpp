#include <allegro5/allegro5.h>
#include "Chip8.h"
#include "ALGraphics.h"
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	Chip8 myChip8;
	stringstream ss;

	ALGraphics graphics;

	if (argc <= 2)
	{
		graphics =  ALGraphics(5);
	}
	else if (argc == 3)
	{
		int width = 0;
		ss << argv[2];
		ss >> width;
		width /= 64;

		graphics =  ALGraphics(width);
	}

	graphics.init();
	myChip8.initialize();

	bool closeGame = false;

	if (argv[1] != NULL)
		myChip8.loadApplication(argv[1]);
	
	while(!closeGame)
	{
		
		myChip8.emulateCycle();
		closeGame = graphics.HandleInput(myChip8);
	}

	return 0;
}
