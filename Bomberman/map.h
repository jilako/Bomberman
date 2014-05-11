#ifndef map_h
#define map_h

typedef struct{
	int inde; // 0=destructible 1=indestructible 2=empty
	int boundX;
	int boundY;
	int displayBonus;
	int bonusType;
} Mur;

typedef struct {
	Mur *contents[15][15];
	int nb_blocks;
}Map;

typedef enum{
	Speed,Strength,Capacity,None
}bonusType;
typedef enum {
	Empty = 0, Block = 1, BlockInd = 2, Player = 3, BombAndPlayer = 4, Bomb = 5
}cases;
void maploading(Map* map);
void mapInitialise(Map* map);
void initialiseWall(Mur *mur,int destr,int x,int y,int bonus);
#endif

