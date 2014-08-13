#pragma once

#include "mobile_object.h"

class Pacman : public MobileObject
{
protected:
	int lives;
	float angle;
	int points;
	int clock_tick;
public:
	Pacman();

	void Init(float x, float y, int boundX,  int boundY, float lives, ALLEGRO_BITMAP *image = NULL);

	void Movement(int keys);

	void ChangeState(int newState);

	void Destroy();
	void Update(int keys);
	void Render();

	void Collided(int ObjectID);
	
	int GetPoints();
	int GetLives();
	int GetState();
	void ResetPoints();
	void TakeLive();
	void Clock();
}; 