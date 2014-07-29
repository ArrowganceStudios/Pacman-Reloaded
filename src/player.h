#pragma once

#include "mobile_object.h"

class Pacman : public MobileObject
{
protected:
	int lives;
public:
	Pacman();

	void Init(float x, float y, int boundX,  int boundY, int velocity, float lives, ALLEGRO_BITMAP *image = NULL);

	void Movement(bool *keys);

	void Destroy();
	void Update(bool *keys);
	void Render();

	void Collided(int ObjectID);
}; 