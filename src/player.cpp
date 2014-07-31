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

	//that makes the Pacman rotating; I don't know if this can be done fancier
	angle = 0;
	flip = false;

	Pacman::image = image;
}

void Pacman::Movement(bool *keys)
{
	if(keys[UP]) 
		{
			MobileObject::MoveUp();
			angle = -ALLEGRO_PI / 2;
			flip = false;
		}
	else if(keys[DOWN]) 
		{
			MobileObject::MoveDown();
			angle = ALLEGRO_PI / 2;
			flip = false;
		}
	else if(keys[LEFT]) 
		{
			MobileObject::MoveLeft();
			angle = 0;
			flip = true;
		}
	else if(keys[RIGHT]) 
		{
			MobileObject::MoveRight();
			angle = 0;
			flip = false;
		}
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
		Pacman::x = WIDTH + 31;
	else if(Pacman::x > WIDTH+32)
		Pacman::x = 1;
	if(Pacman::y < 0)
		Pacman::y = HEIGHT + 31;
	else if (Pacman::y > HEIGHT+32)
		Pacman::y = 1;
	// Now it's smooth and silky
}
void Pacman::Render()
{

	MobileObject::Render();

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	if(flip)
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, 
		al_map_rgba_f(1, 1, 1, 1.0), frameWidth / 2, frameHeight / 2, x - frameWidth / 2, 
		y - frameHeight / 2, 1, 1, angle, ALLEGRO_FLIP_HORIZONTAL); 
	else
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, 
		al_map_rgba_f(1, 1, 1, 1.0), frameWidth / 2, frameHeight / 2, x - frameWidth / 2, 
		y - frameHeight / 2, 1, 1, angle, 0);

}

void Pacman::Collided(int ObjectID)
{

}