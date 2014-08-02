#pragma once

#include "mobile_object.h"
#include "player.h"

class Ghost : public MobileObject
{
protected:
	int animationRows;
public:
	Ghost();

	void Init(float x, float y, int boundX, int boundY, float velocity, ALLEGRO_BITMAP *image);

	void Destroy(){};
	void Update(int map[][21], Pacman &player, int type);
	void Render();

	void AI(int type, Pacman &player);

	void Collided(int ObjectID){};
}; 