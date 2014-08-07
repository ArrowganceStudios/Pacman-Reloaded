#pragma once

#include "mobile_object.h"

class Pacman : public MobileObject
{
protected:
	int lives;
	float angle;
public:
	Pacman();

	void Init(float x, float y, int boundX,  int boundY, float lives,int state, ALLEGRO_BITMAP *image = NULL);

	void Movement(int keys, int map[][21]);

	void  ChangeState(int &state, int newState);

	void Destroy();
	void Update(int keys, int map[][21]);
	void Render();

	void Collided(int ObjectID);
}; 