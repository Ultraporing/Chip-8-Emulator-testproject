#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include "Chip8.h"
#include <stdio.h>

class ALGraphics
{
	private:
		int WIDTH, HEIGHT, FPS, modifier;
		bool redraw;
		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE *eventQueue;
		ALLEGRO_TIMER *timer;
	
	public:
		ALGraphics();
		ALGraphics(int width);
		bool init();
		bool HandleInput(Chip8& chip8);
		bool CleanUp();
};