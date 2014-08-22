#pragma once


#include "game_object.h"
#include "globals.h"
#include <allegro5\allegro.h>

class StaticObject : public GameObject
{
	public:
	StaticObject::StaticObject();

	void Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image);

	void virtual Destroy(){GameObject::Destroy();}
	void virtual Render(){GameObject::Render();}
	
	void virtual Collided(){};
};