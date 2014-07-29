#pragma once

#include "game_object.h"

class MobileObject : public GameObject
{
protected:
	float velocity;

public:
	MobileObject(float x, float y, ALLEGRO_BITMAP *image);

	void Render();
	void Destroy();
	void Update();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Collided(int ObjectID);
};