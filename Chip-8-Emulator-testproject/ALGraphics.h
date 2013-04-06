#pragma once
#include <allegro5/allegro5.h>
#include <stdio.h>

class ALGraphics
{
	private:
		int WIDTH, HEIGHT, FPS;
		bool redraw;
		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE *eventQueue;
		ALLEGRO_TIMER *timer;
	
	public:
		ALGraphics();
		ALGraphics(int width);
		bool init();
		bool HandleInput();
		bool CleanUp();
};