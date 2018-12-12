//Object IDS
enum IDS{PLAYER, BULLET, ENEMY, FRIEND};

//Our Player
struct Player
{
	int ID;
	int x;
	int y;
	int drugs;
	float speed;
	int boundx;
	int boundy;
	int peaces;
    float gravity;
    bool isJumping;
    bool isRising;
    bool firstSpace;
};

//Drug
struct Drug
{
	int ID;
	int x;
	int y;
	bool live;
	int speed;
	int boundx;
	int boundy;
	int type;
};

struct Peace {
	int ID;
	int x;
	int y;
	bool live;
	int speed;
    int boundx;
	int boundy;
};

