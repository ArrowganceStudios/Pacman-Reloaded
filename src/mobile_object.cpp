#include "mobile_object.h"

MobileObject::MobileObject()
{
	GameObject::GameObject();
}

void MobileObject::Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image)
{
	GameObject::Init(x, y, boundX, boundY, image);
}


int MobileObject::MyPositionX()
{
	return (x + 16) / 32;
}
int MobileObject::MyPositionY()
{
	return (y + 16) / 32;
}

void MobileObject::MoveUp()
{
	y -= velocity;
}
void MobileObject::MoveDown()
{
	y += velocity;
}
void MobileObject::MoveLeft()
{
	x -= velocity;
}
void MobileObject::MoveRight()
{
	x += velocity;
}

void MobileObject::Collided(int ObjectID)
{

}