#ifndef player_h
#define player_h
//pma=black dwarf - bob - He be sprinting
//damien=Flying Soul - Icaryss - He be no dying
enum characterChosen {FlyingSoul, BlackDwarf, PersoRomain };
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
} player;



void initialisePlayer(player *p,int number,int x,int y);

#endif