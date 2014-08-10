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
	velocity = 0;

	image = NULL;
};

void Pacman::Init(float x, float y, int boundX,  int boundY, float lives,  ALLEGRO_BITMAP *image)
{
	MobileObject::Init(x, y, boundX, boundY, image);

	Pacman::lives = lives;

	maxFrame = 6;
	curFrame = 0;
	frameCount = 0;								
	frameDelay = 4;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 6;

	points = 0;

	clock_tick = 0;

	angle = 0;

	if(image != NULL)
		Pacman::image = image;

	Pacman::SetDir(-1);
	Pacman::ChangeState(NORMAL);
}

void Pacman::Movement(int keys)
{
	if(keys == UP) 
		{
			if(MobileObject::CanMoveUp() || (int)y % tileSize)
				MobileObject::MoveUp();
			angle = -ALLEGRO_PI / 2;
		}
	else if(keys == DOWN) 
		{
			if(MobileObject::CanMoveDown() || (int)y % tileSize)
				MobileObject::MoveDown();
			angle = ALLEGRO_PI / 2;
		}
	else if(keys == LEFT) 
		{
			if(MobileObject::CanMoveLeft() || (int)x % tileSize)
				MobileObject::MoveLeft();
			angle = ALLEGRO_PI;
		}
	else if(keys == RIGHT) 
		{
			if(MobileObject::CanMoveRight() || (int)x % tileSize)
				MobileObject::MoveRight();
			angle = 0;
		}
}

void Pacman::Destroy()
{
	MobileObject::Destroy();

}

void Pacman::Update(int keys)
{
	Pacman::Movement(direction);
	if((direction != keys) && !((int)x % tileSize) && !((int)y % tileSize))
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
			Pacman::Movement(keys);
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
		Pacman::x = WIDTH + tileSize;
	else if(Pacman::x > WIDTH+31)
		Pacman::x = 0;
	if(Pacman::y < 1)
		Pacman::y = HEIGHT + tileSize;
	else if (Pacman::y > HEIGHT+31)
		Pacman::y = 0;
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

void Pacman::ChangeState(int newState)
{
	if(state == NORMAL)
	{}
	else if(state == POWERUP)
	{
	
	}

	state = newState;

	if(state == NORMAL)
	{
		velocity = 2.3;
	}
	else if(state == POWERUP)
	{
		velocity = 3;
	}
}


int Pacman::GetPoints()
{
	return points;
}

int Pacman::GetLives()
{
	return lives;
}

int Pacman::GetState()
{
	return state;
}

void Pacman::TakeLive()
{
	Pacman::lives--;
}

void Pacman::Collided(int ObjectID)
{
	if(ObjectID == COIN)
		points += 10;
	if(ObjectID == ENEMY)
		if(GetState() == NORMAL)
		{
			ChangeState(DYING);
		}
		//else
			//points += n*200;*/  //where n is number of already eaten ghosts
	if(ObjectID == PILL)
	{
		points += 100; //dunno
		//ChangeState(state, POWERUP);
	}

}

void Pacman::Clock()
{
	if(GetState() == POWERUP)
	{
		clock_tick++;

		if(clock_tick >= 7)
		{
			ChangeState(NORMAL);
			clock_tick = 0;
		}
	}
}