#pragma once

#include "mobile_object.h"
#include "player.h"

class Ghost : public MobileObject
{
protected:
	int animationRows;
public:
	Ghost();

	void Init(float x, float y, int boundX, int boundY, float velocity, ALLEGRO_BITMAP *image = NULL);

	void Destroy(){};
	void Update(int map[][21], float targetX, float targetY, int targetDirection, int type, Ghost &enemy);
	void Render();

	void AI(float targetX, float targetY, int targetDirection, int away, Ghost &enemy);

	float GetDistanceX(float targetX, int dx, Ghost &enemy);
	float GetDistanceY(float targetY, int dy, Ghost &enemy);

	
	void PriorityMovement();

	void Collided(int ObjectID){};
}; 