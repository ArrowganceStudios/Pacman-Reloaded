#pragma once

#include "mobile_object.h"
#include "player.h"

class Ghost : public MobileObject
{
private:
	int away;
	Ghost *enemy;
	Pacman *player;
	float targetX;
	float targetY;
	int targetDirection;
	float ScatterPointX;
	float ScatterPointY;
	int clock_tick;
	int GhostID;

protected:
	int animationRows;
	ALLEGRO_BITMAP *defaultImage;
public:
	static ALLEGRO_BITMAP *fImage;
	static ALLEGRO_BITMAP *eImage;
	Ghost();

	void Init(float x, float y, int boundX, int boundY, Ghost &enemy, Pacman &player,int GhostID, ALLEGRO_BITMAP *image = NULL);

	void Destroy(){};
	void Update();
	void Render();

	void SetImage(ALLEGRO_BITMAP *newImage);

	void ChangeState(int newState);

	void ReverseDirection();

	
	void SetTarget(float targetX, float targetY, int targetDirection,int away);

	void AI(int GhostID);

	float GetDistanceX(float targetX, int dx);
	float GetDistanceY(float targetY, int dy);
	
	void Clock();
	
	void SetScatterPoint(float ScatterPointX, float ScatterPointY);
	
	void RandomMovement();

	void Collided(int ObjectID);
}; 
