#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>

#include "game_object.h"
#include "player.h"
#include "menu.h"
#include "globals.h"
#include "enemy.h"

//Pacman spelt backwards is Hitler

Pacman *player;
Ghost *blacky;				// not racist at all

int main()
{
	////PRIMITIVE VARIABLES
	bool done = false; 																//event loop fundamental variable
	bool redraw = true; 															//check whether the display needs an update
	const int FPS = 60;

	////ALLLEGRO VARIABLES
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bgSheet = NULL;
	ALLEGRO_BITMAP *pmImage = NULL;
	ALLEGRO_BITMAP *ghImage = NULL;

	////INITS
	if(!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);
	if(!display)
		return -1;

	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	player = new Pacman();
	blacky = new Ghost();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	bgSheet = al_load_bitmap("data/img/bg.png");
	pmImage = al_load_bitmap("data/img/pm.png");
	ghImage = al_load_bitmap("data/img/gh.png");

	al_convert_mask_to_alpha(pmImage, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(ghImage, al_map_rgb(255, 255, 255));

	player->Init(WIDTH / 2 + 16, HEIGHT / 2 + 128, 16, 16, 2.5, 3, pmImage);
	blacky->Init(WIDTH / 2 + 16, HEIGHT / 2 + 128, 16, 16, 2, ghImage);

	////EVENT REGISTERS
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	srand(time(NULL));

	////GAMELOOP
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)	
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys = LEFT;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys = RIGHT;
				break;
			case ALLEGRO_KEY_UP:
				keys = UP;
				break;
			case ALLEGRO_KEY_DOWN:
				keys = DOWN;
				break;
			}
			
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true; 												//closing the game after clicking X on top-right corner
		}
		//UPDATE
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;

			player->Update(keys, map);
			blacky->Update(map);
		}
		//RENDERING
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			//drawing map
			for(int i = 0; i < 20; i++)
			{
				for(int j = 0; j < 21; j++)
				{
					al_draw_bitmap_region(bgSheet, tileSize * map[i][j], 0, tileSize, tileSize,
						tileSize * j - 32, tileSize * i, 0);
				}
			}

			

			player->Render();
			blacky->Render();

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0)); 						//black background
		}
	}

	//DEALLOCATING MEMORY

	al_destroy_bitmap(pmImage);
	al_destroy_bitmap(bgSheet);
	al_destroy_bitmap(ghImage);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	return 0;
}