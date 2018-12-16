/********************************

* PROERD GAME
* estruturas de objetos

* IFSC - Florianópolis
* Programação em Linguagem C

* Lucas  de Lacerda Tinoco
* Igor Willy Gretter Peters

* Data: 14/12/2018
* Revisão: 1v0

*********************************/
//IDS dos Objetos
enum IDS{PLAYER, BULLET, ENEMY, FRIEND};

//JOGADOR
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
    bool drugEffect;
};

//DROGAS
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
