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

GameObject::Init(float x, float y, int boundX, int boundY):
x(x), y(y), boundX(boundX), boundY(boundY)
{}

//stuff
void GameObject::Render(){};
void GameObject::Destroy(){};
void GameObject::Update(){};

bool GameObject::CheckCollisions(GameObject *otherObject)
{
	float oX = OtherObject->GetX();
	float oY = OtherObject->GetY();
	int obX = OtherObject->GetBoundX();
	int obY = OtherObject->GetBoundY();

	if( x + boundX > oX - obX &&
		x - boundX < oX + obX &&
		y + boundY > oY - obY &&
		y - boundY < oY + obY)
		return true;
	else 
		return false;
}

void GameObject::Collided(int objectID){};
bool GameObject::Collidable()
{
	return alive && collidable;
}
