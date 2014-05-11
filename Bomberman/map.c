# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "map.h"

void mapInitialise(Map* map){

}

void maploading(Map* map){
	int i;
	int j;
	//case utilisables pour les bonus = 121
	//en ayant que 2 joueurs:
	/*
	20 STR bonus
	10 SPEED bonus
	30 CAPA bonus
	*/
	int STR=20;
	int Quick=10;
	int Capa=15;
	int bonus;
	srand(time(NULL));
	int r;
	int width=800;
	int height=600;
	for(i=0; i<15; i++){
		for(j=0; j<15; j++){
			if(i == 0 || i == 14 || j == 0 || j == 14) {
				// Ajout du contour
				Mur *wall=malloc(sizeof(Mur));
				initialiseWall(wall,1,i*width/15,j*height/15,None); 
				map->contents[i][j] = wall;
				map->nb_blocks++;
			} else if((i == 1 && (j == 2 || j == 12)) || ( i == 2 && (j == 1 || j == 13)) 
				|| (i == 13 && (j == 2 || j == 12)) || (i == 12 && (j == 1 || j == 13))) {
				// Ajout de cases vides aux emplacements de depart
				Mur *wall=malloc(sizeof(Mur));
				initialiseWall(wall,2,i*width/15,j*height/15,None); 
				map->contents[i][j] = wall;
				map->nb_blocks++;
			} else if((i == 1 && (j == 2 || j == 12)) || ( i == 2 && (j == 1 || j == 13)) 
				|| (i == 13 && (j == 2 || j == 12)) || (i == 12 && (j == 1 || j == 13))) {
				// Ajout de blocks destructibles aux emplacements de depart
				r=rand()%10;
				bonus=None;
				if(r<2 && STR>0){
					STR--;
					bonus=Strength;
				}
				else if(r<4 && Capa>0){
					Capa--;
					bonus=Capacity;
				}
				else if(r<6 && Quick>0){
					Quick--;
					bonus=Speed;
				}
				Mur *wall=malloc(sizeof(Mur));
				initialiseWall(wall,0,i*width/15,j*height/15,bonus); 
				map->contents[i][j] = wall;
				map->nb_blocks++;
			} else if(i%2 == 0 && j%2 == 0) {
				// Ajout de blocks indestructibles sur les cases paires (provisoire)
				Mur *wall=malloc(sizeof(Mur));
				initialiseWall(wall,1,i*width/15,j*height/15,None); 
				map->contents[i][j] = wall;
				map->nb_blocks++;
			} else if((i == 1 && (j == 1 || j == 13)) || (i == 13 && (j == 1 || j == 13))) {
				// Ajout des blocks vides aux emplacements des différents joueurs
				Mur *wall=malloc(sizeof(Mur));
				initialiseWall(wall,2,i*width/15,j*height/15,None); 
				map->contents[i][j] = wall;
				map->nb_blocks++;
			} else {
				// Ajoute le reste en block destructible (provisoire)
				bonus=None;
				r=rand()%10;
				if(r<2 && STR>0){
					STR--;
					bonus=Strength;
				}
				else if(r<4 && Capa>0){
					Capa--;
					bonus=Capacity;
				}
				else if(r<6 && Quick>0){
					Quick--;
					bonus=Speed;
				}

					Mur *wall=malloc(sizeof(Mur));
					initialiseWall(wall,0,i*width/15,j*height/15,bonus); 
					map->contents[i][j] = wall;
					map->nb_blocks++;
				}
			}
		}
	}
	void initialiseWall(Mur *mur,int destr,int x,int y,int bonus){
	mur->inde=destr; 
	mur->boundX=x;
	mur->boundY=y;
	mur->bonusType=bonus;
	mur->displayBonus=0;
}
