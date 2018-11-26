//Object IDS
enum IDS{PLAYER, BULLET, ENEMY};

//Our Player
struct Character
{
	int ID;
	int x;
	int y;
	int lives;
	float speed;
	int boundx;
	int boundy;
	int score;
    float gravity;
    bool isJumping;
    bool isRising;
    bool firstSpace;
};

//Obstacle
struct Obstacle
{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
};
