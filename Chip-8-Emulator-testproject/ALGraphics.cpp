#include "ALGraphics.h"


ALGraphics::ALGraphics()
{
	FPS = 200;
	display = NULL;
	eventQueue = NULL;
	timer = NULL;
	redraw = true;
	WIDTH = 64;
	HEIGHT = 32;
	modifier = 1;
}

ALGraphics::ALGraphics(int mod)
{
	modifier = mod;
	FPS = 200;
	display = NULL;
	eventQueue = NULL;
	timer = NULL;
	redraw = true;
	WIDTH = 64 * modifier;
	HEIGHT = 32 * modifier;
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

	al_init_primitives_addon();

	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	al_start_timer(timer);


	return true;
}

bool ALGraphics::HandleInput(Chip8& chip8)
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(eventQueue, &ev);

	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		chip8.drawFlag = true;
	}
	 else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		return CleanUp();
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		
		if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)    // esc
			return CleanUp();

		if(ev.keyboard.keycode == ALLEGRO_KEY_1)		chip8.key[0x1] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_2)	chip8.key[0x2] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_3)	chip8.key[0x3] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_4)	chip8.key[0xC] = 1;

		else if(ev.keyboard.keycode == ALLEGRO_KEY_Q)	chip8.key[0x4] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_W)	chip8.key[0x5] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_E)	chip8.key[0x6] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_R)	chip8.key[0xD] = 1;

		else if(ev.keyboard.keycode == ALLEGRO_KEY_A)	chip8.key[0x7] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_S)	chip8.key[0x8] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_D)	chip8.key[0x9] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_F)	chip8.key[0xE] = 1;

		else if(ev.keyboard.keycode == ALLEGRO_KEY_Y)	chip8.key[0xA] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_X)	chip8.key[0x0] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_C)	chip8.key[0xB] = 1;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_V)	chip8.key[0xF] = 1;
		// keycode stuff set to true
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		if(ev.keyboard.keycode == ALLEGRO_KEY_1)		chip8.key[0x1] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_2)	chip8.key[0x2] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_3)	chip8.key[0x3] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_4)	chip8.key[0xC] = 0;

		else if(ev.keyboard.keycode == ALLEGRO_KEY_Q)	chip8.key[0x4] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_W)	chip8.key[0x5] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_E)	chip8.key[0x6] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_R)	chip8.key[0xD] = 0;

		else if(ev.keyboard.keycode == ALLEGRO_KEY_A)	chip8.key[0x7] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_S)	chip8.key[0x8] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_D)	chip8.key[0x9] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_F)	chip8.key[0xE] = 0;

		else if(ev.keyboard.keycode == ALLEGRO_KEY_Y)	chip8.key[0xA] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_X)	chip8.key[0x0] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_C)	chip8.key[0xB] = 0;
		else if(ev.keyboard.keycode == ALLEGRO_KEY_V)	chip8.key[0xF] = 0;
		// keycode stuff set to false
	}

	

	if (chip8.drawFlag && al_is_event_queue_empty(eventQueue))
	{
		chip8.drawFlag = false;

		al_clear_to_color(al_map_rgb(0, 0, 0));

		for(int y = 0; y < 32; ++y)		
			for(int x = 0; x < 64; ++x)
				if(chip8.gfx[(y * 64) + x] == 0)
				{
					
					//al_draw_filled_rectangle(x, x, y, y, al_map_rgb(0, 0, 0));
					//screenData[y][x][0] = screenData[y][x][1] = screenData[y][x][2] = 0;	// Disabled
					for (int yp = 0; yp < modifier; yp++)
					{
						for (int xp = 0; xp < modifier; xp++)
						{
							al_draw_pixel(((x)*modifier)+xp, ((y)*modifier)+yp, al_map_rgb(0, 0, 0));
						}
					}
				}	
				else 
				{
					
					//al_draw_filled_rectangle(x, x, y, y, al_map_rgb(255, 255, 255));
					// screenData[y][x][0] = screenData[y][x][1] = screenData[y][x][2] = 255;  // Enabled
					for (int yp = 0; yp < modifier; yp++)
					{
						for (int xp = 0; xp < modifier; xp++)
						{
							al_draw_pixel(((x)*modifier)+xp, ((y)*modifier)+yp, al_map_rgb(255, 255, 255));
						}
					}
				}
					

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