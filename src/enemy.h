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

	void AI(Pacman &player, int away);

	float GetDistanceX(Pacman &player, int dx);
	float GetDistanceY(Pacman &player, int dy);

	void Collided(int ObjectID){};
}; 