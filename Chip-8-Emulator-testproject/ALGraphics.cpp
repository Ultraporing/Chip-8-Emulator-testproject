#include "ALGraphics.h"

ALGraphics::ALGraphics()
{
	FPS = 60;
	display = NULL;
	eventQueue = NULL;
	timer = NULL;
	redraw = true;
	WIDTH = 64;
	HEIGHT = 32;
}

ALGraphics::ALGraphics(int width)
{
	FPS = 60;
	display = NULL;
	eventQueue = NULL;
	timer = NULL;
	redraw = true;
	WIDTH = width;
	HEIGHT = width / 2;
}

bool ALGraphics::init()
{
	if (!al_init())
	{
		fprintf_s(stderr, "failed to initialize allegro!\n");
		return false;
	}

	if (!al_install_keyboard())
	{
		fprintf_s(stderr, "failed to initialize keyboard!\n");
		return false;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		fprintf_s(stderr, "failed to create timer!\n");
		return false;
	}

	display = al_create_display(WIDTH, HEIGHT);
	if (!display)
	{
		fprintf_s(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return false;
	}

	eventQueue = al_create_event_queue();
	if (!eventQueue)
	{
		fprintf_s(stderr, "failed to create event queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return false;
	}

	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	al_start_timer(timer);


	return true;
}

bool ALGraphics::HandleInput()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(eventQueue, &ev);

	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		redraw = true;
	}
	else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		return CleanUp();
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		// keycode stuff set to true
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		// keycode stuff set to false
	}

	if (redraw && al_is_event_queue_empty(eventQueue))
	{
		redraw = false;

		al_clear_to_color(al_map_rgb(0, 0, 0));

		// draw emu stuff

		al_flip_display();
	}

	return false;
}

bool ALGraphics::CleanUp()
{
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);

	return true;
}