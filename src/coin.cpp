#include "coin.h"

Coin::Coin()
{
	SetID(COIN);
	StaticObject::StaticObject();
}

void Coin::Init(float x, float y, int boundX, int boundY)
{
	StaticObject::Init(x, y, boundX, boundY, NULL);
	Coin::SetAlive(true);
	Coin::SetCollidable(true);
}

void Coin::Destroy()
{
	Coin::SetAlive(false);
}

void Coin::Render()
{
	al_draw_filled_circle(GetX() - 16, GetY() - 16, 2, al_map_rgb_f(1, 1, 0));			//TEMPORARY
}