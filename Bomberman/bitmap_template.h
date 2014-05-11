#ifndef bitmap_template_h
#define bitmap_template_h
enum MYKEYS{
	KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGTH,SPACE,KEY_ENTER
};
enum DIRECTIONS{
	NORTH,NORTH_EAST,EAST,SOUTH_EAST,SOUTH,SOUTH_WEST,WEST,NORTH_WEST
};
int BB_collision(int appelant,int b1_x, int b1_y,int b1_w,int b1_h, Mur *murs[][15],bomb *bombes[],player **players,player *origin);
void placeBomb(player *p,bomb *bombs[],Mur *murs[][15],int width,int height,int numplayer,player **players);
#endif