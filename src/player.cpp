#include "player.h"

Pacman::Pacman()
{
	MobileObject::MobileObject();
	x = 0;
	y = 0;
	boundX = 0;
	boundY = 0;
	velocity = 1;

	image = NULL;
};

void Pacman::Init(float x, float y, int boundX,  int boundY, int velocity, float lives, ALLEGRO_BITMAP *image)
{
	MobileObject::Init(x, y, boundX, boundY, image);

	Pacman::velocity = velocity;
	Pacman::lives = lives;

	maxFrame = 6;
	curFrame = 0;
	frameCount = 0;								//depends on sprite NEED TO BE FILLED WITH CORRECT VALUES
	frameDelay = 3;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 6;

	Pacman::image = image;
}

void Pacman::Movement(bool *keys)
{
	if(keys[UP]) MobileObject::MoveUp();
	else if(keys[DOWN]) MobileObject::MoveDown();
	else if(keys[LEFT]) MobileObject::MoveLeft();
	else if(keys[RIGHT]) MobileObject::MoveRight();
}

void Pacman::Destroy()
{
	MobileObject::Destroy();

}
void Pacman::Update(bool *keys)
{
	Pacman::Movement(keys);

	if(++frameCount >= frameDelay)
	{
		curFrame ++;
		if(curFrame >= maxFrame)
			curFrame = 0;
		else if(curFrame <= 0)
			curFrame = maxFrame;

		frameCount = 0;
	}
	if(Pacman::x < 0)
		Pacman::x = WIDTH - 1;
	else if(Pacman::x > WIDTH)
		Pacman::x = 1;

}
void Pacman::Render()
{

	MobileObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, 
		al_map_rgba_f(1, 1, 1, 1.0), frameWidth / 2, frameHeight / 2, x - frameWidth / 2, 
		y - frameHeight / 2, 1, 1, 0, 0); //TBI: rotating pacman depending on what dir is he moving to
										  // can be done by changing the penultimate argument to smth like
										  // ALLEGRO_PI / 2, u can try it out yourself

	//al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void Pacman::Collided(int ObjectID)
{

}