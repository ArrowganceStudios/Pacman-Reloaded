#pragma once

#include "game_object.h"

class MobileObject : public GameObject
{
protected:
	float velocity;

public:
	MobileObject::MobileObject(void);

	void Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image);

	void virtual Render(){GameObject::Render();}
	void virtual Destroy(){GameObject::Destroy();}
	void virtual Update(){GameObject::Update();}

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Collided(int ObjectID);
};