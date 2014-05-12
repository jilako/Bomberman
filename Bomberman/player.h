#ifndef player_h
#define player_h

enum characterChosen {FlyingSoul, BlackDwarf, Ninja };
enum specialAttack {speAtt1, speAtt2, speAtt3};
enum orientationPerso {north, east, south, west};

typedef struct {
	int num; //1=speed++ 2=invincible 3=?
	int active;
	int capacityTimer;
} speAtt;

typedef struct {
	char* name;
	int healthPoints;
	int character;
	speAtt spe;
	int orientation;
	int speed;
	int strength;
	int x;		//position du personnage
	int y;
	int boundX;
	int boundY;
	int width;
	int height;
	int typeBomb;
	int bombesPosees;
	int bombCapacity;
	int maxFrameWait;
	int maxFrameWalk;
	int dead;
	bool hasUsed;
} player;



void initialisePlayer(player *p,int number,int x,int y);
void reverse(player *p1,player* p2);
#endif