#pragma once

#include "game_object.h"
#include "globals.h"

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

	int MyPositionX();
	int MyPositionY();

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
};