#include "mobile_object.h"
#include <iostream>

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

int MobileObject::GetColumn()
{
	std::cout << "Column: " << ((int) x) / 32 - 1 << std::endl;
	return ((int) x) / 32 - 1;
}

int MobileObject::GetRow()
{
	std::cout << "Row: " << ((int) y) / 32 - 1 << std::endl;
	return ((int) y) / 32 - 1;
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

bool MobileObject::CanMoveUp()
{
	std::cout << "A One up Row = " << GetRow() - 1 << std::endl;
	std::cout << "A One up Column = " << GetColumn() << std::endl;
	return !(map[GetRow() - 1][GetColumn()]);
}

bool MobileObject::CanMoveDown()
{
	std::cout << "A One down Row = " << GetRow() + 1 << std::endl;
	std::cout << "A One down Column = " << GetColumn() << std::endl;
	return !(map[GetRow() + 1][GetColumn()]);
}

bool MobileObject::CanMoveLeft()
{
	std::cout << "A One left Row = " << GetRow()<< std::endl;
	std::cout << "A One left Column = " << GetColumn() -1 << std::endl;
	return !(map[GetRow()][GetColumn() - 1]);
}
bool MobileObject::CanMoveRight()
{
	std::cout << "A One right Row = " << GetRow() << std::endl;
	std::cout << "A One right Column = " << GetColumn() + 1<< std::endl;
	return !(map[GetRow()][GetColumn() + 1]);
}

void MobileObject::Collided(int ObjectID)
{

}