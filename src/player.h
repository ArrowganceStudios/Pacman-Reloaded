#ifndef PLAYER_H //prevention from repeating includes
#define PLAYER_H
enum KEYS{UP, DOWN, LEFT, RIGHT};

class Pacman
{
	int x;
	int y;
	int boundx;
	int boundy;
	int lives;
	int speed;
	bool mode;
public:
	Pacman(int x, int y, int bx, int by, int lives, int speed, bool mode);
	int GetX();
	int GetY();
	int GetBoundX();
	int GetBoundY();
	int GetLives();
	int GetSpeed();
	bool GetMode();
	void Move(KEYS direction);
};

#endif