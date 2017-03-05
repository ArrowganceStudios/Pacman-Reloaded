#pragma once

#include "game_object.h"
#include "globals.h"
#include "math.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class MobileObject : public GameObject
{
protected:
	float velocity;
	int direction;
	int state;

public:
	MobileObject(void);


	int GetState() {return state;}

	void Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image);

	void virtual Render(){GameObject::Render();}
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
	int GetDirection() {return direction;}

};
