#include <allegro5\allegro.h>
#include "objects.h"

//Global variables
const int WIDTH = 800;
const int HEIGHT = 600;
bool keys[] = {false, false, false, false};

int main()
{
	//primitve variables
	bool done = false; //event loop fundamental variable
	bool redraw = true; //check whether the display needs an update
	const int FPS = 60;
	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	
	//inits
	if(!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);
	if(!display)
		return -1;

	al_install_keyboard();
	
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	//event registers
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	//gameloop
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true; //closing the game after clicking X on top-right corner
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0)); //black background
		}
	}

	//deallocating memory used for allegro objects
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	return 0;
}