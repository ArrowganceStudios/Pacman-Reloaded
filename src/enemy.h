#pragma once

#include "mobile_object.h"
#include "player.h"

class Ghost : public MobileObject
{
private:
	int away;
	Ghost *enemy;
protected:
	int animationRows;
public:
	Ghost();

	void Init(float x, float y, int boundX, int boundY, float velocity, int state, int away, Ghost &enemy, ALLEGRO_BITMAP *image = NULL);

	void Destroy(){};
	void Update(float targetX, float targetY, int targetDirection);
	void Render();

	void ChangeState(int &state, int newState);

	void AI(float targetX, float targetY, int targetDirection);

	float GetDistanceX(float targetX, int dx);
	float GetDistanceY(float targetY, int dy);

	void SetAway(int away) {Ghost::away = away;}

	void SetLeadingGhost(Ghost &enemy) {*Ghost::enemy = enemy;}
	
	void RandomMovement();

	void Collided(int ObjectID){};
}; 