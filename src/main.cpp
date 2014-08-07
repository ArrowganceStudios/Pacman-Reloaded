#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <iostream>
#include <list>

#include "game_object.h"
#include "enemy.h"
#include "player.h"
#include "menu.h"
#include "globals.h"
#include "scatter_point.h"
#include "coin.h"


Pacman *player;

Ghost *blacky;				
Ghost *pinky;	
Ghost *inky;	
Ghost *clyde;	

ScatterPoint *blackysScatterPoint;
ScatterPoint *pinkysScatterPoint;
ScatterPoint *inkysScatterPoint;
ScatterPoint *clydesScatterPoint;

std::list<Coin *> coins;
std::list<Coin *>::iterator iter;

std::list<GameObject*> objects;
std::list<GameObject *>::iterator iter2;

void ChangeState(int &state, int newState);
void ChangePlayingState(int &state, int newState);

int main()
{
	////PRIMITIVE VARIABLES
	bool done = false; 																//event loop fundamental variable
	bool redraw = true; 															//check whether the display needs an update
	const int FPS = 60;
	int ghost_clock = 0;
	int ghost_clock_tick = 0;
	int points = 0;

	int state = -1;
	int PlayingState = -1;


	////ALLLEGRO VARIABLES
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *visitor18 = NULL;

	ALLEGRO_TIMER *timer = NULL;

	ALLEGRO_BITMAP *bgSheet = NULL;
	ALLEGRO_BITMAP *pmImage = NULL;
	ALLEGRO_BITMAP *blackyImage = NULL;
	ALLEGRO_BITMAP *pinkyImage = NULL;
	ALLEGRO_BITMAP *inkyImage = NULL;
	ALLEGRO_BITMAP *clydeImage = NULL;
	ALLEGRO_BITMAP *titleImage = NULL;
	ALLEGRO_BITMAP *lostImage = NULL;

	////INITS
	if(!al_init())
		return -1;

	display = al_create_display(WIDTH, HEIGHT);
	if(!display)
		return -1;

	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	player = new Pacman();
	objects.push_back(player);

	blacky = new Ghost();
	objects.push_back(blacky);

	pinky = new Ghost();
	objects.push_back(pinky);

	inky = new Ghost();
	objects.push_back(inky);

	clyde = new Ghost();
	objects.push_back(clyde);

	blackysScatterPoint = new ScatterPoint();
	pinkysScatterPoint = new ScatterPoint();
	inkysScatterPoint = new ScatterPoint();
	clydesScatterPoint = new ScatterPoint();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	bgSheet = al_load_bitmap("data/img/bg.png");
	pmImage = al_load_bitmap("data/img/pm.png");
	blackyImage = al_load_bitmap("data/img/gh.png");
	pinkyImage = al_load_bitmap("data/img/gh2.png");
	inkyImage = al_load_bitmap("data/img/gh3.png");
	clydeImage = al_load_bitmap("data/img/gh4.png");
	visitor18 = al_load_ttf_font("data/visitor2.ttf", 30, 0);
	titleImage = al_load_bitmap("data/img/pacman_Title.png");
	lostImage = al_load_bitmap("data/img/pacman_Lose.png");

	al_convert_mask_to_alpha(pmImage, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(blackyImage, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(pinkyImage, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(inkyImage, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(clydeImage, al_map_rgb(255, 255, 255));

	player->Init((WIDTH + tileSize) / 2, (HEIGHT + tileSize * 8) / 2, 8, 8, 3, -1, pmImage); 
	blacky->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, -1, 0, *blacky, blackyImage);
	pinky->Init((WIDTH + tileSize * 3) / 2, tileSize * 5, 8, 8, -1, 4, *pinky, pinkyImage);
	inky->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, -1, 2, *blacky, inkyImage);
	clyde->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, -1, 0, *clyde, clydeImage);

	


	////EVENT REGISTERS
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);


	srand(time(NULL));

	ChangeState(state, TITLE);

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
			case ALLEGRO_KEY_ENTER:
				if(state == TITLE)
					ChangeState(state, PLAYING);
				else if(state == LOST)
					ChangeState(state, PLAYING);
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
			if(state == PLAYING)
			{
				ghost_clock++;
				if(ghost_clock >= FPS) 
				{
					ghost_clock_tick++;
					ghost_clock = 0;
				}

				redraw = true;
				player->Update(keys);

				for(iter = coins.begin(); iter != coins.end();)
					if((*iter)->CheckCollisions(player))
					{
						(*iter)->Destroy();
						iter = coins.erase(iter);
						points += 10;
					}
					else iter++;

				if(ghost_clock_tick <= 7) 
				{
					blacky->Update(blackysScatterPoint->GetX(), blackysScatterPoint->GetY(), -1);
					pinky->Update(pinkysScatterPoint->GetX(), pinkysScatterPoint->GetY(), -1);
					inky->Update(inkysScatterPoint->GetX(), inkysScatterPoint->GetY(), -1);
					clyde->Update(clydesScatterPoint->GetX(), clydesScatterPoint->GetY(), -1);
				}

				else if(ghost_clock_tick > 7)
				{
					blacky->Update(player->GetX(), player->GetY(), player->GetDirection());
					pinky->Update(player->GetX(), player->GetY(), player->GetDirection());
					inky->Update(player->GetX(), player->GetY(), player->GetDirection());
					if(sqrt((pow(clyde->GetDistanceX(player->GetX(), 0),2) + pow(clyde->GetDistanceY(player->GetY(), 0),2))) <= 8*tileSize)
						clyde->Update(player->GetX(), player->GetY(), player->GetDirection());
					else 
						clyde->Update(clydesScatterPoint->GetX(), clydesScatterPoint->GetY(), -1);
					if(ghost_clock_tick >= 27) ghost_clock_tick = 0;
				}
			}
		}
		//RENDERING
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			//std::cout << player->CheckDistance(*blacky) << std::endl;
			//drawing map
			if(state ==TITLE)
			{
				al_draw_bitmap(titleImage,0, 0, 0);
				al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH / 2, HEIGHT - 30, ALLEGRO_ALIGN_CENTER, "Press ENTER to play");
			}
			else if(state == PLAYING)
			{
					
				for(int i = 0; i < 20; i++)
				{
					for(int j = 0; j < 21; j++)
					{
						if(!map[i][j])
							al_draw_bitmap_region(bgSheet, 0, 0, tileSize, tileSize,
							tileSize * j - tileSize, tileSize * i, 0);
						else
							al_draw_bitmap_region(bgSheet, tileSize, 0, tileSize, tileSize,
							tileSize * j - tileSize, tileSize * i, 0);
					}
				}

				for(iter = coins.begin(); iter != coins.end(); ++iter)
					(*iter)->Render();

				for(iter2 = objects.begin(); iter2 != objects.end(); ++iter2)
					(*iter2)->Render();
				
				//debug
				/*al_draw_rectangle(player->GetX() - player->GetBoundX(),
								player->GetY() - player->GetBoundY(),
								player->GetX() + player->GetBoundX(),
								player->GetY() + player->GetBoundY(), al_map_rgb_f(1, 1, 1), 1);
				al_draw_rectangle(blacky->GetX() - blacky->GetBoundX(),
								blacky->GetY() - blacky->GetBoundY(),
								blacky->GetX() + blacky->GetBoundX(),
								blacky->GetY() + blacky->GetBoundY(), al_map_rgb_f(1, 1, 1), 1);*/

				al_draw_textf(visitor18, al_map_rgb(255,255,255), 6, 6, 0, "Points: %i", points);
			}
			else if(state == LOST)
			{
				al_draw_bitmap(lostImage,0, 0, 0);
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0)); 						//black background
		}
	}

	//DEALLOCATING MEMORY
	for(iter = coins.begin(); iter != coins.end(); )
	{
			delete (*iter);
			iter = coins.erase(iter);
	}

	for(iter2 = objects.begin(); iter2 != objects.end(); )
	{
			(*iter2)->Destroy();
			delete (*iter2);
			iter2 = objects.erase(iter2);
	}
	
	delete blackysScatterPoint;
	delete pinkysScatterPoint; 
	delete inkysScatterPoint; 
	delete clydesScatterPoint;

	al_destroy_bitmap(titleImage);
	al_destroy_bitmap(lostImage);
	al_destroy_bitmap(pmImage);
	al_destroy_bitmap(bgSheet);
	al_destroy_bitmap(blackyImage);
	al_destroy_bitmap(pinkyImage);
	al_destroy_bitmap(inkyImage);
	al_destroy_bitmap(clydeImage);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	return 0;
}

void ChangeState(int &state, int newState)
{
	if(state ==TITLE)
	{}
	else if(state == PLAYING)
	{}
	else if(state == LOST)
	{}

	state = newState;

	if(state ==TITLE)
	{}
	else if(state == PLAYING)
	{
		
		//scatter points inits
		blackysScatterPoint->Init(tileSize, tileSize * 21);
		pinkysScatterPoint->Init(tileSize * 18, tileSize * 21);
		inkysScatterPoint->Init(tileSize, tileSize);
		clydesScatterPoint->Init(tileSize * 18, tileSize);

		//ghosts inits
		player->Init((WIDTH + tileSize) / 2, (HEIGHT + tileSize * 8) / 2, 8, 8, 3, -1 ); 
		blacky->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, -1, 0, *blacky );
		pinky->Init((WIDTH + tileSize * 3) / 2, tileSize * 5, 8, 8, -1, 4, *pinky );
		inky->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, -1, 2, *blacky );
		clyde->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, -1, 0, *clyde );
	
		//coins inits
		for(int i = 0; i < 21; i++)				
		{
			for(int j = 0; j < 20; j++)
			{
				if(map[i][j] && map[i][j] != 4) //this needs to be done using some new ID tile in the map which will be placed in the ghost house
				{													   //(temporary fix)
					Coin *coin = new Coin();
					coin->Init((j)*tileSize, (i+1)*tileSize, 1, 1);			//TEMPORARY
					coins.push_back(coin);
				}
			}
		}
	}
	else if(state == LOST)
	{}
}

