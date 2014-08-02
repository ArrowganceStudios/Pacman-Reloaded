#pragma once

#include "game_object.h"
#include "globals.h"
#include "math.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

class MobileObject : public GameObject
{
protected:
	float velocity;
	int direction;

public:
	MobileObject::MobileObject(void);

	void Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image);

	void virtual Render(){GameObject::Render();}
	void virtual Destroy(){GameObject::Destroy();}
	void virtual Update(){GameObject::Update();}

	int GetColumn();
	int GetRow();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	bool CanMoveUp();
	bool CanMoveDown();
	bool CanMoveLeft();
	bool CanMoveRight();

	void Collided(int ObjectID);

	void SetDir(int direction) {MobileObject::direction = direction;}

	//float CheckDistance(MobileObject &o) {return sqrt((x-o.x)*(x-o.x) + (y-o.y)*(y-o.y));} //gotta modify this a lil' bit
	float AngleToTarget(MobileObject &o, int dx = 0, int dy = 0) {return atan2(o.y - y + dy, o.x - x + dx);}
};