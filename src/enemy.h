#pragma once

#include "mobile_object.h"
#include "player.h"

class Ghost : public MobileObject
{
protected:
	int animationRows;
public:
	Ghost();

	void Init(float x, float y, int boundX, int boundY, float velocity,int state, ALLEGRO_BITMAP *image = NULL);

	void Destroy(){};
	void Update(int map[][21], float targetX, float targetY, int targetDirection, int away, Ghost &enemy);
	void Render();

	void  ChangeState(int &state, int newState);

	void AI(float targetX, float targetY, int targetDirection, int away, Ghost &enemy);

	float GetDistanceX(float targetX, int dx, Ghost &enemy);
	float GetDistanceY(float targetY, int dy, Ghost &enemy);

	
	void RandomMovement();

	void Collided(int ObjectID){};
}; 