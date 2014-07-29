#include "objects.h"

GameObject::GameObject()
{
	x = 0;
	y = 0;

	boundX = 0;
	boundY = 0;

	maxFrame = 0;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 0;
	frameWidth = 0;
	frameHeight = 0;
	animationColumns = 0;

	image = NULL;

	alive = true;
	collidable = true;
}

GameObject::Init(float x, float y, int boundX, int boundY)
{

	SetX(x);
	SetY(y);

	

}