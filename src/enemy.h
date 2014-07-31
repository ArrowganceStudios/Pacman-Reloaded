#pragma once

#include "mobile_object.h"

class Ghost : public MobileObject
{
public:
	Ghost(float x, float y, ALLEGRO_BITMAP *image);

	void Init(ALLEGRO_BITMAP *image= NULL);

	void Destroy();
	void Update();
	void Render();

	void Collided(int ObjectID);
}; 