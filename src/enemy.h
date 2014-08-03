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
	void Update(int map[][21], Pacman &player, int type, Ghost &enemy);
	void Render();

	void AI(Pacman &player, int away, Ghost &enemy);

	float GetDistanceX(Pacman &player,int dx, Ghost &enemy);
	float GetDistanceY(Pacman &player,int dy, Ghost &enemy);

	
	void PriorityMovement();

	void Collided(int ObjectID){};
}; 