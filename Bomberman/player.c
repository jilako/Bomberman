#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
# include <stdio.h>
# include <time.h>
# include "map.h"
# include "player.h"  //Penser à faire un header ...


# define MAX_HEALTH_POINTS 20


void initialisePlayer(player *p,int number,int x,int y){
	switch(number){
		case BlackDwarf:
		p->name="Bob";
		p->speed=2;
		p->width=32;
		p->height=25;
		p->boundX=32;
		p->boundY=50;
		p->orientation=north;
		p->character=BlackDwarf;
		p->bombCapacity=1;
		p->x=x;
		p->y=y;
		p->bombesPosees=0;
		p->dead=0;
		p->strength=1;
		p->spe.num=1;
		p->spe.active=0;
		p->spe.capacityTimer=75; //environ 5s
		break;
		case FlyingSoul:
		printf("%d %d \n",x,y);
		p->name="Icaryss";
		p->speed=2;
		p->width=32;
		p->height=25;
		p->boundX=45;
		p->boundY=70;
		p->orientation=north;
		p->character=FlyingSoul;
		p->bombCapacity=1;
		p->x=x;
		p->y=y;
		p->bombesPosees=0;
		p->dead=0;
		p->strength=1;
		p->spe.num=2;
		p->spe.active=0;
		p->spe.capacityTimer=25; //environ 1s
	}
}

