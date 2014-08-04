#include "player.h"
#include <iostream>

Pacman::Pacman()
{
	SetID(PLAYER);
	MobileObject::MobileObject();
	x = 0;
	y = 0;
	boundX = 0;
	boundY = 0;
	velocity = 1;

	image = NULL;
};

void Pacman::Init(float x, float y, int boundX,  int boundY, float velocity, float lives, ALLEGRO_BITMAP *image)
{
	MobileObject::Init(x, y, boundX, boundY, image);

	Pacman::velocity = velocity;
	Pacman::lives = lives;

	maxFrame = 6;
	curFrame = 0;
	frameCount = 0;								
	frameDelay = 3;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 6;

	angle = 0;

	Pacman::image = image;
	Pacman::SetDir(-1);
}

void Pacman::Movement(int keys, int map[][21])
{
	if(keys == UP) 
		{
			//std::cout << "is [1][1] free? " << map[10][18] << std::endl;
			//std::cout << "is the one up free? " << map[MobileObject::GetColumn()][MobileObject::GetRow()] << std::endl;
			//std::cout << "is the one up free? " << map[0][0] << std::endl;
			//std::cout << "xC = " << MobileObject::GetColumn() << " yR = " << MobileObject::GetRow() << std::endl;
			//std::cout << "start pos x = " << WIDTH / 2 + 16 << " start pos y = " << HEIGHT / 2 << std::endl;
			//std::cout << "x = " << x << " y = " << y << std::endl;
			//std::cout << "x / 32 " << (int)x / 32 - 1<< " y / 32 " << (int)y / 32 -1<< std::endl;
			//std::cout << "Up?: " << MobileObject::CanMoveUp();
			if(MobileObject::CanMoveUp() || (int)y % 32)
				MobileObject::MoveUp();
			angle = -ALLEGRO_PI / 2;
		}
	else if(keys == DOWN) 
		{
			//std::cout << "down?: " << MobileObject::CanMoveDown();
			if(MobileObject::CanMoveDown() || (int)y % 32)
				MobileObject::MoveDown();
			angle = ALLEGRO_PI / 2;
		}
	else if(keys == LEFT) 
		{
			//std::cout << "left?: " << MobileObject::CanMoveLeft();
			if(MobileObject::CanMoveLeft() || (int)x % 32)
				MobileObject::MoveLeft();
			angle = ALLEGRO_PI;
		}
	else if(keys == RIGHT) 
		{
			//std::cout << "right?: " << MobileObject::CanMoveRight();
			if(MobileObject::CanMoveRight() || (int)x % 32)
				MobileObject::MoveRight();
			angle = 0;
		}
}

void Pacman::Destroy()
{
	MobileObject::Destroy();

}
void Pacman::Update(int keys, int map[][21])
{
	Pacman::Movement(direction, map);
	if((direction != keys) && !((int)x % 32) && !((int)y % 32))
	{
		bool c = false;
		switch(keys)
		{
		case UP:
			if(CanMoveUp()) c = true;
			break;
		case DOWN:
			if(CanMoveDown()) c = true;
			break;
		case RIGHT:
			if(CanMoveRight()) c = true;
			break;
		case LEFT:
			if(CanMoveLeft()) c = true;
			break;
		}

		if(c)
		{
			direction = keys;
			Pacman::Movement(keys, map);
		}
	}

	if(++frameCount >= frameDelay)
	{
		curFrame ++;
		if(curFrame >= maxFrame)
			curFrame = 0;
		else if(curFrame <= 0)
			curFrame = maxFrame;

		frameCount = 0;
	}
	if(Pacman::x < 1)
		Pacman::x = WIDTH + 32;
	else if(Pacman::x > WIDTH+31)
		Pacman::x = 0;
	if(Pacman::y < 1)
		Pacman::y = HEIGHT + 32;
	else if (Pacman::y > HEIGHT+31)
		Pacman::y = 0;
	// Now it's smooth and silky
}
void Pacman::Render()
{

	MobileObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, 
		al_map_rgba_f(1, 1, 1, 1.0), frameWidth / 2, frameHeight / 2, x - frameWidth / 2, 
		y - frameHeight / 2, 1, 1, angle, 0);

}

void Pacman::Collided(int ObjectID)
{

}