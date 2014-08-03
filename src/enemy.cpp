#include "enemy.h"
#include <iostream>
#include "player.h"

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
	Ghost::SetDir(-1);
}
void Ghost::Update(int map[][21], Pacman &player, int type)
{
	/*if(!((int)x % 32) && !((int)y % 32))
	{
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
	}*/
	//AI
	if(!((int)x % 32) && !((int)y % 32) && (map[GetRow()][GetColumn()] == 2))
	{
		AI(type, player);
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

void Ghost::AI(int type, Pacman &player)
{
	float angle;
	switch(type)
	{
	case 0:
		angle = AngleToTarget(player);

		if(abs(x - player.GetX()) > abs(y - player.GetY()) && (CanMoveRight() || CanMoveLeft()))
		{
			if(cos(angle) >= 0 && CanMoveRight() && (direction != LEFT))
				SetDir(RIGHT);
			else if(cos(angle) < 0 && CanMoveLeft() && (direction != RIGHT))
				SetDir(LEFT);
			else
				SetDir(rand() % 2);
		}
		else
		{
			if(sin(angle) >= 0 && CanMoveDown() && (direction != UP))
				SetDir(DOWN);
			else if(sin(angle) < 0 && CanMoveUp() && (direction != DOWN))
				SetDir(UP);
			else
				SetDir(rand() % 2 + 2);
		}
		break;
	case 1: //not finished yet
		angle = 0;
		int dx = 0;
		int dy = 0;

		switch(direction)
		{
		case UP:
			dy += 4*32;
			break;
		case DOWN:
			dy -= 4*32;
			break;
		case RIGHT:
			dx += 4*32;
			break;
		case LEFT:
			dx -= 4*32;
			break;
		}

		angle = AngleToTarget(player, dx, dy);

		if(abs(x - player.GetX() - dx) > abs(y - player.GetY() - dy) && (CanMoveRight() || CanMoveLeft()))
		{
			if(cos(angle) >= 0 && CanMoveRight())
				SetDir(RIGHT);
			else if(cos(angle) < 0 && CanMoveLeft())
				SetDir(LEFT);
			else
				SetDir(rand() % 2);
		}
		else
		{
			if(sin(angle) >= 0 && CanMoveDown())
				SetDir(DOWN);
			else if(sin(angle) < 0 && CanMoveUp())
				SetDir(UP);
			else
				SetDir(rand() % 2 + 2);
		}
		break;
	}
}