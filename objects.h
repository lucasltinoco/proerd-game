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
    int drugEffect;
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

//FRUTAS
struct Peace {
	int ID;
	int x;
	int y;
	bool live;
	int speed;
    int boundx;
	int boundy;
    int type;
};

//struct Cloud {
//    int x;
//    int y;
//    int speed;
//    int type;
//    bool live;
//};
