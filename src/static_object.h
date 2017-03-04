#pragma once


#include "game_object.h"
#include "globals.h"
#include <allegro5/allegro.h>

class StaticObject : public GameObject
{
	public:
	void Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image);

	void virtual Render(){GameObject::Render();}
	
	void virtual Collided(){};
};
