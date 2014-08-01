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

	void Movement(int keys, int map[][19]);

	void Destroy();
	void Update(int keys, int map[][19]);
	void Render();

	void Collided(int ObjectID);
}; 