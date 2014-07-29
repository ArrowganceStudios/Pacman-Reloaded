#pragma once

#include "mobile_object.h"

class Ghost : public mobile_object
{
public:
	Ghost(float x, float y, ALLEGRO_BITMAP *image);

	void Init(ALLEGRO_BITMAP *image= NULL);

	void Destroy();
	void Update();
	void Render();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Collided(int ObjectID);
}; 