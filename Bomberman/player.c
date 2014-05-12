#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
# include <stdio.h>
# include <time.h>
# include "map.h"
# include "player.h"  //Penser à faire un header ...


# define MAX_HEALTH_POINTS 20


void initialisePlayer(player *p,int number,int x,int y){
	switch(number){
		case Ninja:
		p->name="Janin";
		p->speed=2;
		p->width=29;
		p->height=21;
		p->boundX=32;
		p->boundY=61;
		p->orientation=north;
		p->character=Ninja;
		p->bombCapacity=1;
		p->x=x;
		p->y=y;
		p->bombesPosees=0;
		p->dead=0;
		p->strength=1;
		p->spe.num=3;
		p->spe.active=0;
		p->spe.capacityTimer=50; 
		p->hasUsed=false;
		break;
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
		p->hasUsed=false;
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
		p->hasUsed=false;
	}
}
void reverse(player *p1,player *p2){
	int tempo=p1->x;
	int tempo2=p1->y;
	p1->x=p2->x;
	p1->y=p1->y;
	p2->y=tempo2;
	p2->x=tempo;

}

