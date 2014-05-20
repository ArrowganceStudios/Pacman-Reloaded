#include <allegro5\allegro.h>
#include "objects.h"

//Global variables
const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
	//primitve variables
	bool done = false; //event loop fundamental variable

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	
	//inits
	if(!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);
	if(!display)
		return -1;

	al_install_keyboard();
	
	event_queue = al_create_event_queue();

	//event registers
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//gameloop
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
	}

	//deallocating memory used for allegro objects
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}