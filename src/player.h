#pragma once

#include "mobile_object.h"

class Pacman : public MobileObject
{
protected:
	int lives;
	float angle;
public:
	Pacman();

	void Init(float x, float y, int boundX,  int boundY, int velocity, float lives, ALLEGRO_BITMAP *image = NULL);

	void Movement(int keys);

	void Destroy();
	void Update(int keys);
	void Render();

	void Collided(int ObjectID);
}; 