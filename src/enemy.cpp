#include "enemy.h"
#include <iostream>

Ghost::Ghost()
{
	MobileObject::MobileObject();
	x = 0;
	y = 0;
	boundX = 0;
	boundY = 0;
	velocity = 1;

	image = NULL;
}

void Ghost::Init(float x, float y, int boundX, int boundY, float velocity, ALLEGRO_BITMAP *image)
{
	MobileObject::Init(x, y, boundX, boundY, image);

	Ghost::velocity = velocity;

	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;								
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 2;
	animationRows = 4;

	Ghost::image = image;
	Ghost::SetDir(1);
}
void Ghost::Update(int map[][21])
{
	if(!((int)x % 32) && !((int)y % 32))
	{
		std::cout << "elo" << std::endl;
		bool go = false;				// this is the shittiest shitty shit in the shitty history of shit 
		while(!go)
		{
			switch(rand() % 4)
			{
				case UP:
					if(CanMoveUp()) 
					{
						Ghost::SetDir(UP);
						go = true;
					}
					break;
				case DOWN:
					if(CanMoveDown()) 
					{
						Ghost::SetDir(DOWN);
						go = true;
					}
					break;
				case LEFT:
					if(CanMoveLeft()) 
					{
						Ghost::SetDir(LEFT);
						go = true;
					}
					break;
				case RIGHT:
					if(CanMoveRight()) 
					{
						Ghost::SetDir(RIGHT);
						go = true;
					}
					break;
			}
		}
	}
	switch(direction)
	{
		case UP:
			if(CanMoveUp()  || (int)y % 32) MoveUp();
			break;
		case DOWN:
			if(CanMoveDown() || (int)y % 32) MoveDown();
			break;
		case LEFT:
			if(CanMoveLeft() || (int)x % 32) MoveLeft();
			break;
		case RIGHT:
			if(CanMoveRight() || (int)x % 32) MoveRight();
			break;
	}
	if(x < 2)
		x = WIDTH + 32;
	else if(x > WIDTH+30)
		x = 0;
	if(y < 2)
		y = HEIGHT + 32;
	else if (y > HEIGHT+30)
		y = 0;
}

void Ghost::Render()
{
	MobileObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth, y - frameHeight, 0);
}