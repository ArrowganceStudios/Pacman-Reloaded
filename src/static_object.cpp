#include "static_object.h"


	StaticObject::StaticObject()
	{
		GameObject::GameObject();
	}

	void StaticObject::Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image)
	{
		GameObject::Init(x, y, boundX, boundY, image);
	}

	
	