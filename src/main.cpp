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
#include "power_up.h"

Pacman *player;

Ghost *blacky;				
Ghost *pinky;	
Ghost *inky;	
Ghost *clyde;	

ScatterPoint *blackysScatterPoint;
ScatterPoint *pinkysScatterPoint;
ScatterPoint *inkysScatterPoint;
ScatterPoint *clydesScatterPoint;

//std::list<Coin *> coins;
//std::list<Coin *>::iterator iter;

std::list<GameObject*> objects;


std::list<Ghost*> ghosts;  //what do u think about using it?

std::list<GameObject *>::iterator iter;

std::list<Ghost *>::iterator iter2; //what is that for? ~sand3r

void ChangeState(int &state, int newState);

int main()
{
	////PRIMITIVE VARIABLES
	bool done = false; 																//event loop fundamental variable
	bool redraw = true; 															//check whether the display needs an update
	const int FPS = 60;
	int clock = 0;
	int clock_tick = 0;
	int dead_clock = 0;
	int spawn_clock = 0; //this is gotta be moved to the Ghost class as static int, and be prompted from there
	int fright_clock = 0; //same as above
	int state = -1;


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

	player->Init((WIDTH + tileSize) / 2, (HEIGHT + tileSize * 8) / 2, 8, 8, 3, pmImage); 
	blacky->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, *blacky, *player, BLACKY, blackyImage);
	pinky->Init((WIDTH + tileSize * 3) / 2, tileSize * 5, 8, 8, *pinky, *player, PINKY, pinkyImage);
	inky->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, *blacky, *player, INKY, inkyImage);
	clyde->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, *clyde, *player, CLYDE, clydeImage);

	


	////EVENT REGISTERS
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	srand(time(NULL)); //rng

	ChangeState(state, TITLE); // title screen + entering TITLE state

	////GAMELOOP
	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		//Keyboard inputs handeling
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
				if(state != PLAYING)
					ChangeState(state, PLAYING); //entering PLAYING state
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
			if(state == PLAYING) //if we're in playing state
			{
				clock++;	//this shit is gotta be changed keyword: CLOCK
				if(clock >= FPS ) 
				{
					blacky->Clock();
					pinky->Clock();
					inky->Clock();
					clyde->Clock();
					clock = 0;
				}//till here

				redraw = true;

				if(player->GetState() != DYING) // if player is alive
				{
					if(spawn_clock < 2*FPS && spawn_clock++)	//ik it looks dumb, but w/e, didn't have anything better on my mind, sorry.			
						continue;
					else 
					{//after spawning timer
						player->Update(keys);

						//COLLISIONS CHECK
						for(iter = objects.begin(); iter != objects.end(); ++iter)           
						{                                                              
							if( ! (*iter)->Collidable() ) continue;
							if(player->CheckCollisions((*iter)))
							{
								(*iter)->Collided( player->GetID());
								player->Collided( (*iter)->GetID());
								if((*iter)->GetID() == PILL)
								{
									blacky->ChangeState(FRIGHTENED); //ghosts list ?
									pinky->ChangeState(FRIGHTENED);
									inky->ChangeState(FRIGHTENED);
									clyde->ChangeState(FRIGHTENED);

								}
							}
						
						} //endof collisions check

						//destroying dead coins/powerups
						for(iter = objects.begin(); iter != objects.end(); )
						{
							if(((*iter)->GetID() == COIN || (*iter)->GetID() == PILL) && ! (*iter)->GetAlive())    //temporary, should do it by changing collidable and checking collidable somewhere and make action - destroy for coins and changestate to fridgthened for ghosts(cause we dont want ghosts to be destroyed after collided)
							{
								(*iter)->Destroy();
								delete (*iter);
								iter = objects.erase(iter);
							}
							else
								iter++;
						}
						
						//Ghosts update
						for(iter = objects.begin(); iter != objects.end(); ++iter)       //ghosts list ? -    
						{                                                                // ^ good idea ~sand3r
							if((*iter)->GetID() == ENEMY )
								(*iter)->Update();
						}
					}//endif after spawning timer
				} //endif player is alive
				else //if player is dead
				{
					if(++dead_clock > 2*FPS) //dying & spawning pauses
					{
						dead_clock = 0;
						spawn_clock = 0;

						player->TakeLive();
						if(player->GetLives() > 0) //if player still got lives left
						{
							ChangeState(state, PLAYING); //entering PLAYING state again, even tho we're inside it. (to reinitialize pacaman and ghosts position)
							player->ChangeState(NORMAL);
						}
						else
							ChangeState(state, LOST);
					}
				}
			} //endif playing state
		}
		//RENDERING
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			if(state ==TITLE) //drawing title screen
			{
				al_draw_bitmap(titleImage,0, 0, 0);
				al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH / 2, HEIGHT - 30, ALLEGRO_ALIGN_CENTER, "Press ENTER to play");
			}
			else if(state == PLAYING) //in PLAYING state
			{	//drawing map
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

				//rendering remaining coins/powerups
				for(iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if((*iter)->GetID() == COIN || (*iter)->GetID() == PILL)
						(*iter)->Render();
				}
				
				//rendering player & ghosts
				for(iter = objects.begin(); iter != objects.end(); ++iter)
				{
					if((*iter)->GetID() == ENEMY || (*iter)->GetID() == PLAYER)
						(*iter)->Render();
				}

				//rendering remaining points text
				al_draw_textf(visitor18, al_map_rgb(255,255,255), 6, 6, 0, "Points: %i", player->GetPoints());

				//debug for ghost states
				al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH / 2, BLACKY*30, ALLEGRO_ALIGN_CENTER, "blacky %i",blacky->GetState());
				al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH / 2, PINKY*30, ALLEGRO_ALIGN_CENTER, "pinky %i", pinky->GetState());
				al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH / 2, INKY*30, ALLEGRO_ALIGN_CENTER, "inky %i", inky->GetState());
				al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH / 2,  CLYDE*30, ALLEGRO_ALIGN_CENTER, "clyde %i", clyde->GetState());
				
				//rendering remaining lives
				for(int i = 0; i < player->GetLives(); i++)
					al_draw_filled_circle(20*(i+1), HEIGHT - 14, 7, al_map_rgb_f(1, 1, 0));
				
				//rendering text after pacman's death
				if(player->GetState() == DYING) al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "lel faget");
				
				//rendering text at the start of the round
				if(spawn_clock < 2 * FPS) al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2, ALLEGRO_ALIGN_CENTER, "Ready?");
			} //endif PLAYING state
			else if(state == LOST) //lost screen
			{
				al_draw_bitmap(lostImage,0, 0, 0);
				al_draw_textf(visitor18, al_map_rgb(255,255,255), WIDTH / 2, HEIGHT - 30, ALLEGRO_ALIGN_CENTER, "Press ENTER to play again");
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0)); 						//black background
		}
	}

	//DEALLOCATING MEMORY
	

	for(iter = objects.begin(); iter != objects.end(); )
	{
			(*iter)->Destroy();
			delete (*iter);
			iter = objects.erase(iter);
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
	if(state == PLAYING)
		player->Init((WIDTH + tileSize) / 2, (HEIGHT + tileSize * 8) / 2, 8, 8, player->GetLives()); 
	else if(state == LOST || state == TITLE)
	{
		player->Init((WIDTH + tileSize) / 2, (HEIGHT + tileSize * 8) / 2, 8, 8, 3); 

		//coins inits
		for(iter = objects.begin(); iter != objects.end();)			//removing old coins/pills
		{
			if((*iter)->GetID() == COIN || (*iter)->GetID() == PILL)
				iter = objects.erase(iter);
			else iter++;
		}
		//spawning new coins
		for(int i = 0; i < 21; i++)				
		{
			for(int j = 0; j < 20; j++)
			{
				if(map[i][j] && map[i][j] != 4 &&  map[i][j] != 5 )
				{
					Coin *coin = new Coin();
					coin->Init((j)*tileSize, (i+1)*tileSize, 1, 1);			//TEMPORARY
					objects.push_back(coin);
				}
				else if(map[i][j]  == 5)
				{
					PowerUp *powerup = new PowerUp();
					powerup->Init((j)*tileSize, (i+1)*tileSize, 6, 6);			//TEMPORARY
					objects.push_back(powerup);
				}
			}
		}
	}

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
		blacky->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8,*blacky, *player, BLACKY);
		pinky->Init((WIDTH + tileSize * 3) / 2, tileSize * 5, 8, 8, *pinky, *player, PINKY);
		inky->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8,*blacky, *player, INKY);
		clyde->Init((WIDTH + tileSize) / 2, tileSize * 5, 8, 8, *clyde, *player, CLYDE);

		
		blacky->SetScatterPoint(blackysScatterPoint->GetX(), blackysScatterPoint->GetY());
		pinky->SetScatterPoint(pinkysScatterPoint->GetX(), pinkysScatterPoint->GetY());
		inky->SetScatterPoint(inkysScatterPoint->GetX(), inkysScatterPoint->GetY());
		clyde->SetScatterPoint(clydesScatterPoint->GetX(), clydesScatterPoint->GetY());
	}
	else if(state == LOST)
	{
		
	}
}

