#ifndef bomb_h
#define bomb_h
typedef struct
{
	int x;
	int y;
	int flaming;
	int width;
	player owner;
	int active; //1=active, 0=inactive
	int explosionTimer;
	int bombDamages;	// Elles font toutes MAX_HEALTH_POINTS de dégats ... A enlever ?
	enum {
		Normale, Incendiaire, Givrante, Empoisonnante// ... 			avec Incendiaire : même dégats que la normale mais mets des flammes sur les cases voisines  / Givrante : même dégats que la normale mais gele le sol sur les cases voisines -> prévoir effet indésirable ...
	}typeBomb;
} bomb;
void explosion(bomb b, int k, player* p, player* p1, player* p2, Map* map,bomb *Bombes[]);
void initialiseBomb(bomb *kaboom,player *p,int x,int y);
void trigger(bomb *kaboom, int active);
#endif