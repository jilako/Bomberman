# include <stdio.h>
# include "map.h"
# include "player.h"
# include "bomb.h"  //Penser à faire un header ...
#define BLOCK_WIDTH 53
#define BLOCK_HEIGHT 40 

// Bombe qui va exploser, son rang dans le tableau des bombes, le joueur qui l'a posée, joueur 1, joueur 2, map, tableau des bombes
void explosion(bomb b, int k, player* p, player* p1, player* p2, Map* map,bomb *Bombes[]){
    int i;
    int j;
    char *soundBombExplosion="effects/explosion.wav";
    char *soundDeath="effects/death.wav";

    playSound(soundBombExplosion);
            for(i=0 ; i<=p->strength ; i++){


                /* --------------------------------------------
                   |                                           |
                   |                                          |
                   |       explosion des blocs à l'est        |
                   |                                          |
                   |                                          |
                   --------------------------------------------*/
                   int b1_x=p1->x+p1->boundX+BLOCK_WIDTH*i;
                   int b1_y=p1->y+p1->boundY;
                   int b1_w=p1->width;
                   int b1_h=p1->height;
                   int b2_x=b.x;
                   int b2_y=b.y;
                   int b2_w=BLOCK_WIDTH;
                   int b2_h=BLOCK_HEIGHT;
            if ((b1_x < b2_x + b2_w ) && 
                    (b1_y < b2_y + b2_h ) && 
                    (b2_x < b1_x + b1_w ) && 
                    (b2_y < b1_y + b1_h ))  
                {
                    printf("YOOOOLOOO \n");
                }
                //si la case à l'est n'est pas un bloc indestructible
                if(map->contents[(b.x)/BLOCK_WIDTH+i][(b.y)/BLOCK_HEIGHT]->inde!=1){

                    
                    if((b.x)/BLOCK_WIDTH+i==(p1->x+p1->boundX)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT==(p1->y+p1->boundY)/BLOCK_HEIGHT){
                        // Si c'est le joueur1, qui a le joueur Soul et qui a activé sa capacité spé
                        if(p1->spe.num==2 && p1->spe.active==1){
                        p1->dead=0;         //alors le joueur survit
                        } else {
                            p1->dead=1;        // sinon il meurt
                            playSound(soundDeath);
                            p1->x=-200;
                            p1->y=-200;
                        }
                    }

                    if((b.x)/BLOCK_WIDTH+i==(p2->x+p2->boundX)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT==(p2->y+p2->boundY)/BLOCK_HEIGHT){
                        // Si c'est le joueur2, qui a le joueur Soul et qui a activé sa capacité spé
                        if(p2->spe.num==2 && p2->spe.active==1){
                        p2->dead=0;        //alors le joueur survit
                        } else {
                            p2->dead=1; // sinon il meurt
                            playSound(soundDeath);
                            p2->x=-200;
                            p2->y=-200;
                        }
                    }

                    for(j=0; j<=7 ; j++){
                        //Si c'est une bombe ...
                        if((b.x)/BLOCK_WIDTH+i==(Bombes[j]->x)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT==(Bombes[j]->y)/BLOCK_HEIGHT){
                            if(k!=j && Bombes[j]->active==1){ //... qui n'est pas la meme bombe alors ...
                                Bombes[j]->explosionTimer=1;
                            }
                        }
                    }
                    if(map->contents[(b.x)/BLOCK_WIDTH+i][(b.y)/BLOCK_HEIGHT]->inde!=2)
                    map->contents[(b.x)/BLOCK_WIDTH+i][(b.y)/BLOCK_HEIGHT]->displayBonus=1;
                    map->contents[(b.x)/BLOCK_WIDTH+i][(b.y)/BLOCK_HEIGHT]->inde=2;        //La case est finalement vidée
                } else { break; }

                /* --------------------------------------------
                   |                                           |
                   |                                          |
                   |       explosion des blocs à l'ouest      |
                   |                                          |
                   |                                          |
                   --------------------------------------------*/

            
            }
            for(i=0 ; i<=p->strength ; i++){
                              int b1_x=p1->x+p1->boundX-BLOCK_WIDTH*i;
                   int b1_y=p1->y+p1->boundY;
                   int b1_w=p1->width;
                   int b1_h=p1->height;
                   int b2_x=b.x;
                   int b2_y=b.y;
                   int b2_w=BLOCK_WIDTH;
                   int b2_h=BLOCK_HEIGHT;
            if ((b1_x < b2_x + b2_w ) && 
                    (b1_y < b2_y + b2_h ) && 
                    (b2_x < b1_x + b1_w ) && 
                    (b2_y < b1_y + b1_h ))  
                {
                    printf("YOOOOLOOO \n");
                }
                if(map->contents[(b.x)/BLOCK_WIDTH-i][(b.y)/BLOCK_HEIGHT]->inde!=1){
                    if((b.x)/BLOCK_WIDTH-i==(p1->x+p1->boundX)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT==(p1->y+p1->boundY)/BLOCK_HEIGHT){
                        
                        if(p1->spe.num==2 && p1->spe.active==1){
                        p1->dead=0;
                        } else {
                            p1->dead=1;
                            playSound(soundDeath);
                            p1->x=-200;
                            p1->y=-200;
                        }
                    }
                    if((b.x)/BLOCK_WIDTH-i==(p2->x+p2->boundX)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT==(p2->y+p2->boundY)/BLOCK_HEIGHT){
                        
                        if(p2->spe.num==2 && p2->spe.active==1){
                        p2->dead=0;playSound(soundDeath);
                        } else {
                            p2->dead=1;
                            playSound(soundDeath);
                            p2->x=-200;
                            p2->y=-200;
                        }
                    }
                    for(j=0; j<=7 ; j++){
                        if((b.x)/BLOCK_WIDTH-i==(Bombes[j]->x)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT==(Bombes[j]->y)/BLOCK_HEIGHT){
                            if(k!=j && Bombes[j]->active==1){
                                Bombes[j]->explosionTimer=1;
                            }
                        }
                    }
                    if( map->contents[(b.x)/BLOCK_WIDTH-i][(b.y)/BLOCK_HEIGHT]->inde!=2)
                    map->contents[(b.x)/BLOCK_WIDTH-i][(b.y)/BLOCK_HEIGHT]->displayBonus=1;
                    map->contents[(b.x)/BLOCK_WIDTH-i][(b.y)/BLOCK_HEIGHT]->inde=2;
                } else { break; }
            }

                /* --------------------------------------------
                   |                                           |
                   |                                          |
                   |       explosion des blocs au sud         |
                   |                                          |
                   |                                          |
                   --------------------------------------------*/

            for(i=0 ; i<=p->strength ; i++){
                              int b1_x=p1->x+p1->boundX;
                   int b1_y=p1->y+p1->boundY+BLOCK_HEIGHT*i;
                   int b1_w=p1->width;
                   int b1_h=p1->height;
                   int b2_x=b.x;
                   int b2_y=b.y;
                   int b2_w=BLOCK_WIDTH;
                   int b2_h=BLOCK_HEIGHT;
            if ((b1_x < b2_x + b2_w ) && 
                    (b1_y < b2_y + b2_h ) && 
                    (b2_x < b1_x + b1_w ) && 
                    (b2_y < b1_y + b1_h ))  
                {
                     if(p1->spe.num==2 && p1->spe.active==1){
                        p1->dead=0;
                        } else {
                            p1->dead=1;
                            playSound(soundDeath);
                            p1->x=-200;
                            p1->y=-200;
                        }
                }
                if(map->contents[(b.x)/BLOCK_WIDTH][(b.y)/BLOCK_HEIGHT+i]->inde!=1 ){
                    if((b.x)/BLOCK_WIDTH==(p1->x+p1->boundX)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT+i==(p1->y+p1->boundY)/BLOCK_HEIGHT){
                        
                        if(p1->spe.num==2 && p1->spe.active==1){
                        p1->dead=0;
                        } else {
                            p1->dead=1;
                            playSound(soundDeath);
                            p1->x=-200;
                            p1->y=-200;
                        }
                    }
                    
                    if((b.x)/BLOCK_WIDTH==(p2->x+p2->boundX)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT+i==(p2->y+p2->boundY)/BLOCK_HEIGHT){
                        
                        if(p2->spe.num==2 && p2->spe.active==1){
                        p2->dead=0;
                        } else {
                            p2->dead=1;
                            playSound(soundDeath);
                            p2->x=-200;
                            p2->y=-200;
                        }
                    }
                    for(j=0; j<=7 ; j++){
                        if((b.x)/BLOCK_WIDTH==(Bombes[j]->x)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT+i==(Bombes[j]->y)/BLOCK_HEIGHT){
                            if(k!=j && Bombes[j]->active==1){
                                Bombes[j]->explosionTimer=1;
                            }
                        }
                    }
                    if(map->contents[(b.x)/BLOCK_WIDTH][(b.y)/BLOCK_HEIGHT+i]->inde!=2)
                    map->contents[(b.x)/BLOCK_WIDTH][(b.y)/BLOCK_HEIGHT+i]->displayBonus=1;
                    map->contents[(b.x)/BLOCK_WIDTH][(b.y)/BLOCK_HEIGHT+i]->inde=2;
                } else { break; }
            }

                /* --------------------------------------------
                   |                                           |
                   |                                          |
                   |       explosion des blocs au nord        |
                   |                                          |
                   |                                          |
                   --------------------------------------------*/
                    int b1_x=p1->x+p1->boundX;
                   int b1_y=p1->y+p1->boundY-BLOCK_HEIGHT*i;
                   int b1_w=p1->width;
                   int b1_h=p1->height;
                   int b2_x=b.x;
                   int b2_y=b.y;
                   int b2_w=BLOCK_WIDTH;
                   int b2_h=BLOCK_HEIGHT;
            if ((b1_x < b2_x + b2_w ) && 
                    (b1_y < b2_y + b2_h ) && 
                    (b2_x < b1_x + b1_w ) && 
                    (b2_y < b1_y + b1_h ))  
                {
                     if(p->spe.num==2 && p->spe.active==1){
                        p->dead=0;
                        } else {
                            p->dead=1;
                            playSound(soundDeath);
                            p->x=-200;
                            p->y=-200;
                        }
                }
            for(i=0 ; i<=p->strength ; i++){
                if(map->contents[(b.x)/BLOCK_WIDTH][(b.y)/BLOCK_HEIGHT-i]->inde!=1){
                    if((b.x)/BLOCK_WIDTH==(p->x+p->boundX)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT-i==(p->y+p->boundY)/BLOCK_HEIGHT){
                        
                        if(p->spe.num==2 && p->spe.active==1){
                        p->dead=0;
                        } else {
                            p->dead=1;
                            playSound(soundDeath);
                            p->x=-200;
                            p->y=-200;
                        }
                    }
                    if((b.x)/BLOCK_WIDTH==(p->x+p->boundX)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT-i==(p->y+p->boundY)/BLOCK_HEIGHT){
                        
                        if(p->spe.num==2 && p->spe.active==1){
                        p->dead=0;
                        } else {
                            p->dead=1;
                            playSound(soundDeath);
                            p->x=-200;
                            p->y=-200;
                        }
                    }
                    for(j=0; j<=7 ; j++){
                        if((b.x)/BLOCK_WIDTH==(Bombes[j]->x)/BLOCK_WIDTH && (b.y)/BLOCK_HEIGHT-i==(Bombes[j]->y)/BLOCK_HEIGHT){
                            if(k!=j && Bombes[j]->active==1){
                                Bombes[j]->explosionTimer=1;
                            }
                        }
                    }
                    if(map->contents[(b.x)/BLOCK_WIDTH][(b.y)/BLOCK_HEIGHT-i]->inde!=2)
                    map->contents[(b.x)/BLOCK_WIDTH][(b.y)/BLOCK_HEIGHT-i]->displayBonus=1;
                    map->contents[(b.x)/BLOCK_WIDTH][(b.y)/BLOCK_HEIGHT-i]->inde=2;
                } else { break; }
            }
}
void initialiseBomb(bomb *kaboom,player *p,int x,int y){
	kaboom->x=x;
	kaboom->y=y;
	kaboom->width=30;
	kaboom->owner=*p;
	kaboom->active=0;
	kaboom->explosionTimer=70;
	kaboom->flaming=0;
}
void trigger(bomb *kaboom, int active){
	char *soundBombPlacement="effects/placementBomb.wav";
	kaboom->active=active;
	playSound(soundBombPlacement);
	if(active==0){
		kaboom->explosionTimer=50;
	}
//	printf("kaboom : %d",kaboom->active);
}