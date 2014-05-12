#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "allegro5/allegro_primitives.h"
#include "map.h"
#include "player.h"
#include "bomb.h"
#include "bitmap_template.h"
#include "sound.h"
#include <stdio.h>
#include "xc.h"

#define BLOCK_WIDTH 53
#define BLOCK_HEIGHT 40 
#define map_width 15
#define map_height 15
int main(void)
{
    //constantes
    const int DwarfmaxFrameWait = 12;
    const int DwarfmaxFrameWalk = 8;
    const int SoulMaxFrame=16;
    const int NinjaMaxFrame=8;
    //variables
    Map *map=malloc(sizeof(Map));
    mapInitialise(map);
    maploading(map);
    bomb *Bombes[8];
    player *players[2];
    char *fileSoundMain="effects/DST-CyberOps.ogg";
    int width = 800;
    int height = 600;
    int bomb_frame=0;
    int j;  
    int hasIndeLeft=-1;
    int hasIndeTop=-1;
    int hasIndeBottom=-1;
    int hasIndeRight=-1;
    int choix_def=-1;
    int choix=FlyingSoul;
    int choix2;
    int shieldFrame=0;
    int auraFrame=0;
    int i;
    int x = 25;
    int y = 10;
    bool done = false;
    bool pressureRight=false;
    bool pressureLeft=false;
    bool redraw=true;
    bool IsP1Moving = false;
    bool IsP1Moving1 = false;
    bool IsP1Moving2 = false;
    bool IsP1Moving3 = false;
    bool IsP1Moving4 = false;
    bool IsP2Moving1 =false;
    bool IsP2Moving2 = false;
    bool IsP2Moving = false;
    bool p2Bomb=false;
    bool Bomb_placed=false;
    bool capacityON=false;
    //Dwarf frames
    int DwarfCurFrameWaiting = 0;
    int DwarfCurFrameWalking=0;
    int DwarfFrameCountWait = 0;
    int DwarfFrameCountWalk = 0;
    //Soul frames
    int SoulCurFrame=0;
    int SoulFrameCount=0;
    //Ninja frames
    int NinjaCurFrame=0;
    int NinjaFrameCount=0;
    
    //controller
    XC_STATE *xc=malloc(sizeof(XC_STATE));
    xc_get_state(xc);

    player *p1=malloc(sizeof(player));
    player *p2=malloc(sizeof(player));

    int frameDelay = 5;
    bool key[6]={false,false,false,false,false,false};
    //INITIALISE BOMBS
    for (i = 0;i<8;i++){
        Bombes[i]=malloc(sizeof(bomb));
        if(i<4)
            initialiseBomb( Bombes[i],p1,0,0);
        else 
            initialiseBomb( Bombes[i],p2,0,0);          
    }
        //TEXT
    ALLEGRO_BITMAP *text;
    ALLEGRO_BITMAP *text2;
    ALLEGRO_BITMAP *text3;
    ALLEGRO_BITMAP *winner;
    //DOGE
    ALLEGRO_BITMAP *doge;
    //DREAMS
    ALLEGRO_BITMAP *dreams;
    //allegro variable
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue_menu =NULL;
    ALLEGRO_EVENT_QUEUE *event_queue_fin = NULL;
    ALLEGRO_TIMER *timer;

    //DWARF
    ALLEGRO_BITMAP *dwarfWaitingEast[DwarfmaxFrameWait];
    ALLEGRO_BITMAP *dwarfWaitingNorth[DwarfmaxFrameWait];
    ALLEGRO_BITMAP *dwarfWaitingWest[DwarfmaxFrameWait];
    ALLEGRO_BITMAP *dwarfWaitingSouth[DwarfmaxFrameWait];
    ALLEGRO_BITMAP *dwarfMovingEast[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *dwarfMovingWest[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *dwarfMovingNorth[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *dwarfMovingSouth[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *dwarfRunningEast[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *dwarfRunningWest[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *dwarfRunningNorth[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *dwarfRunningSouth[DwarfmaxFrameWalk];

    //SOUL
    ALLEGRO_BITMAP *soulEast[SoulMaxFrame];
    ALLEGRO_BITMAP *soulWest[SoulMaxFrame];
    ALLEGRO_BITMAP *soulNorth[SoulMaxFrame];
    ALLEGRO_BITMAP *soulSouth[SoulMaxFrame];
    //NINJA
    ALLEGRO_BITMAP *ninjaEast[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *ninjaWest[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *ninjaNorth[DwarfmaxFrameWalk];
    ALLEGRO_BITMAP *ninjaSouth[DwarfmaxFrameWalk];
    //FIRE
    ALLEGRO_BITMAP *fire_horizontal;
    ALLEGRO_BITMAP *fire_vertical;
    ALLEGRO_BITMAP *fire_end_left;
    ALLEGRO_BITMAP *fire_end_right;
    ALLEGRO_BITMAP *fire_end_top;
    ALLEGRO_BITMAP *fire_end_bottom;
    ALLEGRO_BITMAP *fire_cross;

    //SOUL SHIELD
    ALLEGRO_BITMAP *shield[31];
    //AURA
    ALLEGRO_BITMAP *aura[16];
    //BOMBS
    ALLEGRO_BITMAP *bomb[16];
    //BLOCKS
    ALLEGRO_BITMAP *block[2];
    //BONUS
    ALLEGRO_BITMAP *bonus[3];
    //program init
    if(!al_init())                                      //initialize Allegro
        return -1;

    display = al_create_display(width, height);         
    if(!display)                                        
        return -1;

    //addon init
    al_install_keyboard();
    al_install_joystick();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(6);
    //DECLARATION DES FRAMES
    block[0]=al_load_bitmap("bombs/ExplodableBlock.png");
    block[1]=al_load_bitmap("bombs/SolidBlock.png");

    fire_horizontal=al_load_bitmap("bombs/fire_horizontal.png");
    fire_vertical =al_load_bitmap("bombs/fire_vertical.png");
    fire_end_left =al_load_bitmap("bombs/end_fire_left.png");
    fire_end_right =al_load_bitmap("bombs/end_fire_right.png");
    fire_end_top =al_load_bitmap("bombs/end_fire_top.png");
    fire_end_bottom =al_load_bitmap("bombs/end_fire_bottom.png");
    fire_cross=al_load_bitmap("bombs/cross_fire.png");
    dreams=al_load_bitmap("bombs/dreams.jpg");
    doge=al_load_bitmap("bombs/shibe.jpg");
    winner=al_load_bitmap("bombs/winner.png");
    bomb[0]=al_load_bitmap("bombs/bomb.png");
    bomb[1]=al_load_bitmap("bombs/bomb.png");
    bomb[2]=al_load_bitmap("bombs/bomb.png");
    bomb[3]=al_load_bitmap("bombs/bomb.png");
    bomb[4]=al_load_bitmap("bombs/bomb.png");
    bomb[5]=al_load_bitmap("bombs/bomb.png");
    bomb[6]=al_load_bitmap("bombs/bomb.png");
    bomb[7]=al_load_bitmap("bombs/bomb.png");
    bomb[8]=al_load_bitmap("bombs/bomb_neg.png");
    bomb[9]=al_load_bitmap("bombs/bomb_neg.png");
    bomb[10]=al_load_bitmap("bombs/bomb_neg.png");
    bomb[11]=al_load_bitmap("bombs/bomb_neg.png");
    bomb[12]=al_load_bitmap("bombs/bomb_neg.png");
    bomb[13]=al_load_bitmap("bombs/bomb_neg.png");
    bomb[14]=al_load_bitmap("bombs/bomb_neg.png");
    bomb[15]=al_load_bitmap("bombs/bomb_neg.png");

    dwarfWaitingEast[0] = al_load_bitmap("T_darkdwarf/looking e0001.bmp");
    dwarfWaitingEast[1] = al_load_bitmap("T_darkdwarf/looking e0002.bmp");
    dwarfWaitingEast[2] = al_load_bitmap("T_darkdwarf/looking e0003.bmp");
    dwarfWaitingEast[3] = al_load_bitmap("T_darkdwarf/looking e0004.bmp");
    dwarfWaitingEast[4] = al_load_bitmap("T_darkdwarf/looking e0005.bmp");
    dwarfWaitingEast[5] = al_load_bitmap("T_darkdwarf/looking e0006.bmp");
    dwarfWaitingEast[6] = al_load_bitmap("T_darkdwarf/looking e0007.bmp");
    dwarfWaitingEast[7] = al_load_bitmap("T_darkdwarf/looking e0008.bmp");
    dwarfWaitingEast[8] = al_load_bitmap("T_darkdwarf/looking e0009.bmp");
    dwarfWaitingEast[9] = al_load_bitmap("T_darkdwarf/looking e0010.bmp");
    dwarfWaitingEast[10] = al_load_bitmap("T_darkdwarf/looking e0011.bmp");
    dwarfWaitingEast[11] = al_load_bitmap("T_darkdwarf/looking e0000.bmp");
    dwarfWaitingWest[0] = al_load_bitmap("T_darkdwarf/looking w0001.bmp");
    dwarfWaitingWest[1] = al_load_bitmap("T_darkdwarf/looking w0002.bmp");
    dwarfWaitingWest[2] = al_load_bitmap("T_darkdwarf/looking w0003.bmp");
    dwarfWaitingWest[3] = al_load_bitmap("T_darkdwarf/looking w0004.bmp");
    dwarfWaitingWest[4] = al_load_bitmap("T_darkdwarf/looking w0005.bmp");
    dwarfWaitingWest[5] = al_load_bitmap("T_darkdwarf/looking w0006.bmp");
    dwarfWaitingWest[6] = al_load_bitmap("T_darkdwarf/looking w0007.bmp");
    dwarfWaitingWest[7] = al_load_bitmap("T_darkdwarf/looking w0008.bmp");
    dwarfWaitingWest[8] = al_load_bitmap("T_darkdwarf/looking w0009.bmp");
    dwarfWaitingWest[9] = al_load_bitmap("T_darkdwarf/looking w0010.bmp");
    dwarfWaitingWest[10] = al_load_bitmap("T_darkdwarf/looking w0011.bmp");
    dwarfWaitingWest[11] = al_load_bitmap("T_darkdwarf/looking w0000.bmp");
    dwarfWaitingSouth[0] = al_load_bitmap("T_darkdwarf/looking s0001.bmp");
    dwarfWaitingSouth[1] = al_load_bitmap("T_darkdwarf/looking s0002.bmp");
    dwarfWaitingSouth[2] = al_load_bitmap("T_darkdwarf/looking s0003.bmp");
    dwarfWaitingSouth[3] = al_load_bitmap("T_darkdwarf/looking s0004.bmp");
    dwarfWaitingSouth[4] = al_load_bitmap("T_darkdwarf/looking s0005.bmp");
    dwarfWaitingSouth[5] = al_load_bitmap("T_darkdwarf/looking s0006.bmp");
    dwarfWaitingSouth[6] = al_load_bitmap("T_darkdwarf/looking s0007.bmp");
    dwarfWaitingSouth[7] = al_load_bitmap("T_darkdwarf/looking s0008.bmp");
    dwarfWaitingSouth[8] = al_load_bitmap("T_darkdwarf/looking s0009.bmp");
    dwarfWaitingSouth[9] = al_load_bitmap("T_darkdwarf/looking s0010.bmp");
    dwarfWaitingSouth[10] = al_load_bitmap("T_darkdwarf/looking s0011.bmp");
    dwarfWaitingSouth[11] = al_load_bitmap("T_darkdwarf/looking s0000.bmp");
    dwarfWaitingNorth[0] = al_load_bitmap("T_darkdwarf/looking n0001.bmp");
    dwarfWaitingNorth[1] = al_load_bitmap("T_darkdwarf/looking n0002.bmp");
    dwarfWaitingNorth[2] = al_load_bitmap("T_darkdwarf/looking n0003.bmp");
    dwarfWaitingNorth[3] = al_load_bitmap("T_darkdwarf/looking n0004.bmp");
    dwarfWaitingNorth[4] = al_load_bitmap("T_darkdwarf/looking n0005.bmp");
    dwarfWaitingNorth[5] = al_load_bitmap("T_darkdwarf/looking n0006.bmp");
    dwarfWaitingNorth[6] = al_load_bitmap("T_darkdwarf/looking n0007.bmp");
    dwarfWaitingNorth[7] = al_load_bitmap("T_darkdwarf/looking n0008.bmp");
    dwarfWaitingNorth[8] = al_load_bitmap("T_darkdwarf/looking n0009.bmp");
    dwarfWaitingNorth[9] = al_load_bitmap("T_darkdwarf/looking n0010.bmp");
    dwarfWaitingNorth[10] = al_load_bitmap("T_darkdwarf/looking n0011.bmp");
    dwarfWaitingNorth[11] = al_load_bitmap("T_darkdwarf/looking n0000.bmp");
    dwarfMovingEast[0] = al_load_bitmap("T_darkdwarf/walking e0001.bmp");
    dwarfMovingEast[1] = al_load_bitmap("T_darkdwarf/walking e0002.bmp");
    dwarfMovingEast[2] = al_load_bitmap("T_darkdwarf/walking e0003.bmp");
    dwarfMovingEast[3] = al_load_bitmap("T_darkdwarf/walking e0004.bmp");
    dwarfMovingEast[4] = al_load_bitmap("T_darkdwarf/walking e0005.bmp");
    dwarfMovingEast[5] = al_load_bitmap("T_darkdwarf/walking e0006.bmp");
    dwarfMovingEast[6] = al_load_bitmap("T_darkdwarf/walking e0007.bmp");
    dwarfMovingEast[7] = al_load_bitmap("T_darkdwarf/walking e0000.bmp");
    dwarfMovingWest[0] = al_load_bitmap("T_darkdwarf/walking w0001.bmp");
    dwarfMovingWest[1] = al_load_bitmap("T_darkdwarf/walking w0002.bmp");
    dwarfMovingWest[2] = al_load_bitmap("T_darkdwarf/walking w0003.bmp");
    dwarfMovingWest[3] = al_load_bitmap("T_darkdwarf/walking w0004.bmp");
    dwarfMovingWest[4] = al_load_bitmap("T_darkdwarf/walking w0005.bmp");
    dwarfMovingWest[5] = al_load_bitmap("T_darkdwarf/walking w0006.bmp");
    dwarfMovingWest[6] = al_load_bitmap("T_darkdwarf/walking w0007.bmp");
    dwarfMovingWest[7] = al_load_bitmap("T_darkdwarf/walking w0000.bmp");
    dwarfMovingNorth[0] = al_load_bitmap("T_darkdwarf/walking n0001.bmp");
    dwarfMovingNorth[1] = al_load_bitmap("T_darkdwarf/walking n0002.bmp");
    dwarfMovingNorth[2] = al_load_bitmap("T_darkdwarf/walking n0003.bmp");
    dwarfMovingNorth[3] = al_load_bitmap("T_darkdwarf/walking n0004.bmp");
    dwarfMovingNorth[4] = al_load_bitmap("T_darkdwarf/walking n0005.bmp");
    dwarfMovingNorth[5] = al_load_bitmap("T_darkdwarf/walking n0006.bmp");
    dwarfMovingNorth[6] = al_load_bitmap("T_darkdwarf/walking n0007.bmp");
    dwarfMovingNorth[7] = al_load_bitmap("T_darkdwarf/walking n0000.bmp");
    dwarfMovingSouth[0] = al_load_bitmap("T_darkdwarf/walking s0001.bmp");
    dwarfMovingSouth[1] = al_load_bitmap("T_darkdwarf/walking s0002.bmp");
    dwarfMovingSouth[2] = al_load_bitmap("T_darkdwarf/walking s0003.bmp");
    dwarfMovingSouth[3] = al_load_bitmap("T_darkdwarf/walking s0004.bmp");
    dwarfMovingSouth[4] = al_load_bitmap("T_darkdwarf/walking s0005.bmp");
    dwarfMovingSouth[5] = al_load_bitmap("T_darkdwarf/walking s0006.bmp");
    dwarfMovingSouth[6] = al_load_bitmap("T_darkdwarf/walking s0007.bmp");
    dwarfMovingSouth[7] = al_load_bitmap("T_darkdwarf/walking s0000.bmp");
    dwarfRunningEast[0] = al_load_bitmap("T_darkdwarf/running e0001.bmp");
    dwarfRunningEast[1] = al_load_bitmap("T_darkdwarf/running e0002.bmp");
    dwarfRunningEast[2] = al_load_bitmap("T_darkdwarf/running e0003.bmp");
    dwarfRunningEast[3] = al_load_bitmap("T_darkdwarf/running e0004.bmp");
    dwarfRunningEast[4] = al_load_bitmap("T_darkdwarf/running e0005.bmp");
    dwarfRunningEast[5] = al_load_bitmap("T_darkdwarf/running e0006.bmp");
    dwarfRunningEast[6] = al_load_bitmap("T_darkdwarf/running e0007.bmp");
    dwarfRunningEast[7] = al_load_bitmap("T_darkdwarf/running e0000.bmp");
    dwarfRunningWest[0] = al_load_bitmap("T_darkdwarf/running w0001.bmp");
    dwarfRunningWest[1] = al_load_bitmap("T_darkdwarf/running w0002.bmp");
    dwarfRunningWest[2] = al_load_bitmap("T_darkdwarf/running w0003.bmp");
    dwarfRunningWest[3] = al_load_bitmap("T_darkdwarf/running w0004.bmp");
    dwarfRunningWest[4] = al_load_bitmap("T_darkdwarf/running w0005.bmp");
    dwarfRunningWest[5] = al_load_bitmap("T_darkdwarf/running w0006.bmp");
    dwarfRunningWest[6] = al_load_bitmap("T_darkdwarf/running w0007.bmp");
    dwarfRunningWest[7] = al_load_bitmap("T_darkdwarf/running w0000.bmp");
    dwarfRunningNorth[0] = al_load_bitmap("T_darkdwarf/running n0001.bmp");
    dwarfRunningNorth[1] = al_load_bitmap("T_darkdwarf/running n0002.bmp");
    dwarfRunningNorth[2] = al_load_bitmap("T_darkdwarf/running n0003.bmp");
    dwarfRunningNorth[3] = al_load_bitmap("T_darkdwarf/running n0004.bmp");
    dwarfRunningNorth[4] = al_load_bitmap("T_darkdwarf/running n0005.bmp");
    dwarfRunningNorth[5] = al_load_bitmap("T_darkdwarf/running n0006.bmp");
    dwarfRunningNorth[6] = al_load_bitmap("T_darkdwarf/running n0007.bmp");
    dwarfRunningNorth[7] = al_load_bitmap("T_darkdwarf/running n0000.bmp");
    dwarfRunningSouth[0] = al_load_bitmap("T_darkdwarf/running s0001.bmp");
    dwarfRunningSouth[1] = al_load_bitmap("T_darkdwarf/running s0002.bmp");
    dwarfRunningSouth[2] = al_load_bitmap("T_darkdwarf/running s0003.bmp");
    dwarfRunningSouth[3] = al_load_bitmap("T_darkdwarf/running s0004.bmp");
    dwarfRunningSouth[4] = al_load_bitmap("T_darkdwarf/running s0005.bmp");
    dwarfRunningSouth[5] = al_load_bitmap("T_darkdwarf/running s0006.bmp");
    dwarfRunningSouth[6] = al_load_bitmap("T_darkdwarf/running s0007.bmp");
    dwarfRunningSouth[7] = al_load_bitmap("T_darkdwarf/running s0000.bmp");




    soulEast[0] = al_load_bitmap("soul/flying e0001.bmp");
    soulEast[1] = al_load_bitmap("soul/flying e0002.bmp");
    soulEast[2] = al_load_bitmap("soul/flying e0003.bmp");
    soulEast[3] = al_load_bitmap("soul/flying e0004.bmp");
    soulEast[4] = al_load_bitmap("soul/flying e0005.bmp");
    soulEast[5] = al_load_bitmap("soul/flying e0006.bmp");
    soulEast[6] = al_load_bitmap("soul/flying e0007.bmp");
    soulEast[7] = al_load_bitmap("soul/flying e0008.bmp");
    soulEast[8] = al_load_bitmap("soul/flying e0009.bmp");
    soulEast[9] = al_load_bitmap("soul/flying e0010.bmp");
    soulEast[10] = al_load_bitmap("soul/flying e0011.bmp");
    soulEast[11] = al_load_bitmap("soul/flying e0012.bmp");
    soulEast[12] = al_load_bitmap("soul/flying e0013.bmp");
    soulEast[13] = al_load_bitmap("soul/flying e0014.bmp");
    soulEast[14] = al_load_bitmap("soul/flying e0015.bmp");
    soulEast[15] = al_load_bitmap("soul/flying e0000.bmp");
    soulWest[0] = al_load_bitmap("soul/flying w0001.bmp");
    soulWest[1] = al_load_bitmap("soul/flying w0002.bmp");
    soulWest[2] = al_load_bitmap("soul/flying w0003.bmp");
    soulWest[3] = al_load_bitmap("soul/flying w0004.bmp");
    soulWest[4] = al_load_bitmap("soul/flying w0005.bmp");
    soulWest[5] = al_load_bitmap("soul/flying w0006.bmp");
    soulWest[6] = al_load_bitmap("soul/flying w0007.bmp");
    soulWest[7] = al_load_bitmap("soul/flying w0008.bmp");
    soulWest[8] = al_load_bitmap("soul/flying w0009.bmp");
    soulWest[9] = al_load_bitmap("soul/flying w0010.bmp");
    soulWest[10] = al_load_bitmap("soul/flying w0011.bmp");
    soulWest[11] = al_load_bitmap("soul/flying w0012.bmp");
    soulWest[12] = al_load_bitmap("soul/flying w0013.bmp");
    soulWest[13] = al_load_bitmap("soul/flying w0014.bmp");
    soulWest[14] = al_load_bitmap("soul/flying w0015.bmp");
    soulWest[15] = al_load_bitmap("soul/flying w0000.bmp");
    soulNorth[0] = al_load_bitmap("soul/flying n0001.bmp");
    soulNorth[1] = al_load_bitmap("soul/flying n0002.bmp");
    soulNorth[2] = al_load_bitmap("soul/flying n0003.bmp");
    soulNorth[3] = al_load_bitmap("soul/flying n0004.bmp");
    soulNorth[4] = al_load_bitmap("soul/flying n0005.bmp");
    soulNorth[5] = al_load_bitmap("soul/flying n0006.bmp");
    soulNorth[6] = al_load_bitmap("soul/flying n0007.bmp");
    soulNorth[7] = al_load_bitmap("soul/flying n0008.bmp");
    soulNorth[8] = al_load_bitmap("soul/flying n0009.bmp");
    soulNorth[9] = al_load_bitmap("soul/flying n0010.bmp");
    soulNorth[10] = al_load_bitmap("soul/flying n0011.bmp");
    soulNorth[11] = al_load_bitmap("soul/flying n0012.bmp");
    soulNorth[12] = al_load_bitmap("soul/flying n0013.bmp");
    soulNorth[13] = al_load_bitmap("soul/flying n0014.bmp");
    soulNorth[14] = al_load_bitmap("soul/flying n0015.bmp");
    soulNorth[15] = al_load_bitmap("soul/flying n0000.bmp");
    soulSouth[0] = al_load_bitmap("soul/flying s0001.bmp");
    soulSouth[1] = al_load_bitmap("soul/flying s0002.bmp");
    soulSouth[2] = al_load_bitmap("soul/flying s0003.bmp");
    soulSouth[3] = al_load_bitmap("soul/flying s0004.bmp");
    soulSouth[4] = al_load_bitmap("soul/flying s0005.bmp");
    soulSouth[5] = al_load_bitmap("soul/flying s0006.bmp");
    soulSouth[6] = al_load_bitmap("soul/flying s0007.bmp");
    soulSouth[7] = al_load_bitmap("soul/flying s0008.bmp");
    soulSouth[8] = al_load_bitmap("soul/flying s0009.bmp");
    soulSouth[9] = al_load_bitmap("soul/flying s0010.bmp");
    soulSouth[10] = al_load_bitmap("soul/flying s0011.bmp");
    soulSouth[11] = al_load_bitmap("soul/flying s0012.bmp");
    soulSouth[12] = al_load_bitmap("soul/flying s0013.bmp");
    soulSouth[13] = al_load_bitmap("soul/flying s0014.bmp");
    soulSouth[14] = al_load_bitmap("soul/flying s0015.bmp");
    soulSouth[15] = al_load_bitmap("soul/flying s0000.bmp");

    bonus[0] =al_load_bitmap("bombs/CapaBonus.png");
    bonus[1] =al_load_bitmap("bombs/StrengthBonus.png");
    bonus[2] =al_load_bitmap("bombs/SpeedBonus.png");

    shield[0]=al_load_bitmap("shield/blue aura appearing 0000.bmp");
    shield[1]=al_load_bitmap("shield/blue aura appearing 0001.bmp");
    shield[2]=al_load_bitmap("shield/blue aura appearing 0002.bmp");
    shield[3]=al_load_bitmap("shield/blue aura appearing 0003.bmp");
    shield[4]=al_load_bitmap("shield/blue aura appearing 0004.bmp");
    shield[5]=al_load_bitmap("shield/blue aura appearing 0005.bmp");
    shield[6]=al_load_bitmap("shield/blue aura appearing 0006.bmp");
    shield[7]=al_load_bitmap("shield/blue aura appearing 0007.bmp");
    shield[8]=al_load_bitmap("shield/blue aura appearing 0008.bmp");
    shield[9]=al_load_bitmap("shield/blue aura appearing 0009.bmp");
    shield[10]=al_load_bitmap("shield/blue aura appearing 0010.bmp");
    shield[11]=al_load_bitmap("shield/blue aura appearing 0011.bmp");
    shield[12]=al_load_bitmap("shield/blue aura appearing 0012.bmp");
    shield[13]=al_load_bitmap("shield/blue aura appearing 0013.bmp");
    shield[14]=al_load_bitmap("shield/blue aura appearing 0014.bmp");
    shield[15]=al_load_bitmap("shield/blue aura appearing 0015.bmp");
    shield[16]=al_load_bitmap("shield/blue aura disappearing 0001.bmp");
    shield[17]=al_load_bitmap("shield/blue aura disappearing 0002.bmp");
    shield[18]=al_load_bitmap("shield/blue aura disappearing 0003.bmp");
    shield[19]=al_load_bitmap("shield/blue aura disappearing 0004.bmp");
    shield[20]=al_load_bitmap("shield/blue aura disappearing 0005.bmp");
    shield[21]=al_load_bitmap("shield/blue aura disappearing 0006.bmp");
    shield[22]=al_load_bitmap("shield/blue aura disappearing 0007.bmp");
    shield[23]=al_load_bitmap("shield/blue aura disappearing 0008.bmp");
    shield[24]=al_load_bitmap("shield/blue aura disappearing 0009.bmp");
    shield[25]=al_load_bitmap("shield/blue aura disappearing 0010.bmp");
    shield[26]=al_load_bitmap("shield/blue aura disappearing 0011.bmp");
    shield[27]=al_load_bitmap("shield/blue aura disappearing 0012.bmp");
    shield[28]=al_load_bitmap("shield/blue aura disappearing 0013.bmp");
    shield[29]=al_load_bitmap("shield/blue aura disappearing 0014.bmp");
    shield[30]=al_load_bitmap("shield/blue aura disappearing 0015.bmp");
    ninjaSouth[0]=al_load_bitmap("ninja/walking s0000.bmp");
    ninjaSouth[1]=al_load_bitmap("ninja/walking s0001.bmp");
    ninjaSouth[2]=al_load_bitmap("ninja/walking s0002.bmp");
    ninjaSouth[3]=al_load_bitmap("ninja/walking s0003.bmp");
    ninjaSouth[4]=al_load_bitmap("ninja/walking s0004.bmp");
    ninjaSouth[5]=al_load_bitmap("ninja/walking s0005.bmp");
    ninjaSouth[6]=al_load_bitmap("ninja/walking s0006.bmp");
    ninjaSouth[7]=al_load_bitmap("ninja/walking s0007.bmp");
    ninjaNorth[0]=al_load_bitmap("ninja/walking n0000.bmp");
    ninjaNorth[1]=al_load_bitmap("ninja/walking n0001.bmp");
    ninjaNorth[2]=al_load_bitmap("ninja/walking n0002.bmp");
    ninjaNorth[3]=al_load_bitmap("ninja/walking n0003.bmp");
    ninjaNorth[4]=al_load_bitmap("ninja/walking n0004.bmp");
    ninjaNorth[5]=al_load_bitmap("ninja/walking n0005.bmp");
    ninjaNorth[6]=al_load_bitmap("ninja/walking n0006.bmp");
    ninjaNorth[7]=al_load_bitmap("ninja/walking n0007.bmp");
    ninjaWest[0]=al_load_bitmap("ninja/walking w0000.bmp");
    ninjaWest[1]=al_load_bitmap("ninja/walking w0001.bmp");
    ninjaWest[2]=al_load_bitmap("ninja/walking w0002.bmp");
    ninjaWest[3]=al_load_bitmap("ninja/walking w0003.bmp");
    ninjaWest[4]=al_load_bitmap("ninja/walking w0004.bmp");
    ninjaWest[5]=al_load_bitmap("ninja/walking w0005.bmp");
    ninjaWest[6]=al_load_bitmap("ninja/walking w0006.bmp");
    ninjaWest[7]=al_load_bitmap("ninja/walking w0007.bmp");
    ninjaEast[0]=al_load_bitmap("ninja/walking e0000.bmp");
    ninjaEast[1]=al_load_bitmap("ninja/walking e0001.bmp");
    ninjaEast[2]=al_load_bitmap("ninja/walking e0002.bmp");
    ninjaEast[3]=al_load_bitmap("ninja/walking e0003.bmp");
    ninjaEast[4]=al_load_bitmap("ninja/walking e0004.bmp");
    ninjaEast[5]=al_load_bitmap("ninja/walking e0005.bmp");
    ninjaEast[6]=al_load_bitmap("ninja/walking e0006.bmp");
    ninjaEast[7]=al_load_bitmap("ninja/walking e0007.bmp");

    aura[0]=al_load_bitmap("aura/blue aura0000.bmp");
    aura[1]=al_load_bitmap("aura/blue aura0001.bmp");
    aura[2]=al_load_bitmap("aura/blue aura0002.bmp");
    aura[3]=al_load_bitmap("aura/blue aura0003.bmp");
    aura[4]=al_load_bitmap("aura/blue aura0004.bmp");
    aura[5]=al_load_bitmap("aura/blue aura0005.bmp");
    aura[6]=al_load_bitmap("aura/blue aura0006.bmp");
    aura[7]=al_load_bitmap("aura/blue aura0007.bmp");
    aura[8]=al_load_bitmap("aura/blue aura0008.bmp");
    aura[9]=al_load_bitmap("aura/blue aura0009.bmp");
    aura[10]=al_load_bitmap("aura/blue aura0010.bmp");
    aura[11]=al_load_bitmap("aura/blue aura0011.bmp");
    aura[12]=al_load_bitmap("aura/blue aura0012.bmp");
    aura[13]=al_load_bitmap("aura/blue aura0013.bmp");
    aura[14]=al_load_bitmap("aura/blue aura0014.bmp");
    aura[15]=al_load_bitmap("aura/blue aura0015.bmp");
    text=al_load_bitmap("bombs/text.jpg");
    text2=al_load_bitmap("bombs/text2.jpg");
    text3=al_load_bitmap("bombs/text3.jpg");
//Transparence en mettant des masques sur les images pour faire disparaître les fonds
    for( i = 0; i < SoulMaxFrame; i++){
        if(i<DwarfmaxFrameWait){
            al_convert_mask_to_alpha(dwarfWaitingEast[i], al_map_rgb(97, 68, 43));
            al_convert_mask_to_alpha(dwarfWaitingNorth[i], al_map_rgb(97, 68, 43));
            al_convert_mask_to_alpha(dwarfWaitingWest[i], al_map_rgb(97, 68, 43));
            al_convert_mask_to_alpha(dwarfWaitingSouth[i], al_map_rgb(97, 68, 43));
            if (i < DwarfmaxFrameWalk){
                al_convert_mask_to_alpha(ninjaEast[i],al_map_rgb(106,76,48));
                al_convert_mask_to_alpha(ninjaWest[i],al_map_rgb(106,76,48));
                al_convert_mask_to_alpha(ninjaNorth[i],al_map_rgb(106,76,48));
                al_convert_mask_to_alpha(ninjaSouth[i],al_map_rgb(106,76,48));
                al_convert_mask_to_alpha(dwarfMovingEast[i], al_map_rgb(97, 68, 43));
                al_convert_mask_to_alpha(dwarfMovingNorth[i], al_map_rgb(97, 68, 43));
                al_convert_mask_to_alpha(dwarfMovingWest[i], al_map_rgb(97, 68, 43));
                al_convert_mask_to_alpha(dwarfMovingSouth[i], al_map_rgb(97, 68, 43));
                al_convert_mask_to_alpha(dwarfRunningEast[i], al_map_rgb(97, 68, 43));
                al_convert_mask_to_alpha(dwarfRunningNorth[i], al_map_rgb(97, 68, 43));
                al_convert_mask_to_alpha(dwarfRunningWest[i], al_map_rgb(97, 68, 43));
                al_convert_mask_to_alpha(dwarfRunningSouth[i], al_map_rgb(97, 68, 43));
            }
        }
        al_convert_mask_to_alpha(soulEast[i],al_map_rgb(128,128,128));
        al_convert_mask_to_alpha(soulWest[i],al_map_rgb(128,128,128));
        al_convert_mask_to_alpha(soulNorth[i],al_map_rgb(128,128,128));
        al_convert_mask_to_alpha(soulSouth[i],al_map_rgb(128,128,128));
    }
    for (i = 0; i < 31; ++i)
    {
        al_convert_mask_to_alpha(shield[i],al_map_rgb(191,123,199));
        if(i<16){
            al_convert_mask_to_alpha(aura[i],al_map_rgb(128,128,128));
        }
    }
    al_convert_mask_to_alpha(fire_vertical,al_map_rgb(0,192,192));
    al_convert_mask_to_alpha(fire_horizontal,al_map_rgb(0,192,192));
    al_convert_mask_to_alpha(fire_end_right,al_map_rgb(0,192,192));
    al_convert_mask_to_alpha(fire_end_left,al_map_rgb(0,192,192));
    al_convert_mask_to_alpha(fire_end_top,al_map_rgb(0,192,192));
    al_convert_mask_to_alpha(fire_end_bottom,al_map_rgb(0,192,192));
    al_convert_mask_to_alpha(fire_cross,al_map_rgb(0,192,192));
        //FPS 
    timer = al_create_timer(1.0 / 120);
    event_queue = al_create_event_queue();
    //GESTION DU MENU DE CHOIX DES JOUEURS
    event_queue_menu=al_create_event_queue();
    //on enregistre les sources d'évenements
    al_register_event_source(event_queue_menu,al_get_display_event_source(display));
    al_register_event_source(event_queue_menu,al_get_timer_event_source(timer));
    al_register_event_source(event_queue_menu,al_get_keyboard_event_source());
    al_register_event_source(event_queue_menu,al_get_joystick_event_source());
    al_start_timer(timer);

    //Lancement du son
    playMainSound(fileSoundMain);
    while(choix_def<0){
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue_menu,&ev);
        if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            return 1;
        }
        if(ev.type==ALLEGRO_EVENT_JOYSTICK_AXIS ||
            ev.type==ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN ||
            ev.type==ALLEGRO_EVENT_JOYSTICK_BUTTON_UP){
            xc_update(ev,xc);
    }
    if(ev.type== ALLEGRO_EVENT_KEY_DOWN){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
            choix_def=choix;
            break;

        }
    }
    if(xc->button_x){
        choix2=0;
    }
    if(xc->button_y){
        choix2=1;
    }
    if(xc->button_b){
        choix2=2;
    }
    if(pressureRight){
        choix++;
        pressureRight=false;
    }
    if(pressureLeft){
        choix--;
        pressureLeft=false;
    }
    if(ev.type== ALLEGRO_EVENT_KEY_UP){
        switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
            choix_def=choix;
            break;
            case ALLEGRO_KEY_LEFT:
            choix--;
            break;
            case ALLEGRO_KEY_RIGHT:
            choix++;
            break;
            case ALLEGRO_KEY_ENTER:
            choix_def=choix;
            break;
        }
    }
    if (choix==3){
        choix=2;
    }
    if(choix==-1){
        choix=0;
    }
    else if(ev.type == ALLEGRO_EVENT_TIMER)
    {
                    //gestion des frames pour le blackDwarf
        if(++DwarfFrameCountWait >= frameDelay)
        {
            if(++DwarfCurFrameWaiting >= DwarfmaxFrameWait)
                DwarfCurFrameWaiting = 0;

            DwarfFrameCountWait= 0;
        }


            //gestion des frames pour le flying soul
        if(++SoulFrameCount >= frameDelay)
        {
            if(++SoulCurFrame >= SoulMaxFrame)
                SoulCurFrame = 0;

            SoulFrameCount= 0;
        }

            //gestion des frames pour le ninja
        if(++NinjaFrameCount >= frameDelay)
        {
            if(++NinjaCurFrame >= NinjaMaxFrame)
                NinjaCurFrame = 0;

            NinjaFrameCount= 0;
        }
        redraw=true;
    }
        //on trace à l'écran
    if(redraw && al_is_event_queue_empty(event_queue_menu)) 
    {
        al_draw_bitmap(dreams,100,0,0);
        if(choix==0){
            al_draw_bitmap(bomb[0],235,335,0);
        }
        else if (choix == 1){
            al_draw_bitmap(bomb[0],360,335,0);
        }
        else{
            al_draw_bitmap(bomb[0],490,335,0);
        }
        if(choix2==0){
            al_draw_bitmap(bomb[10],235,335,0);
        }
        else if(choix2==1){
            al_draw_bitmap(bomb[10],360,335,0);
        }
        else if (choix2==2){
            al_draw_bitmap(bomb[10],490,335,0);
        }
        al_draw_bitmap(text,225,370,0);
        al_draw_bitmap(text2,350,370,0);
         al_draw_bitmap(text3,480,370,0);
        al_draw_bitmap(dwarfWaitingSouth[DwarfCurFrameWaiting],200, 260, 0);
        al_draw_bitmap(soulSouth[SoulCurFrame],320,250,0);
        al_draw_bitmap(ninjaSouth[NinjaCurFrame],470,260,0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(250,250,250));
        redraw=false;
    }
}
    //on libère la file d'évènements
al_destroy_event_queue(event_queue_menu);
    //on assigne aux joueurs les personnages
if(choix_def==0){
    initialisePlayer(p1,BlackDwarf,x,y);
    players[0]=p1;
}
else if(choix_def==1){
    initialisePlayer(p1,FlyingSoul,x,y);
    players[0]=p1;
}
else{
    initialisePlayer(p1,Ninja,x,y);
    players[0]=p1;
}
if(choix2==1){
    initialisePlayer(p2,FlyingSoul,width-2*BLOCK_WIDTH-30,0);
    players[1]=p2;
}
if(choix2==0){
    initialisePlayer(p2,BlackDwarf,width-2*BLOCK_WIDTH-30,0);
    players[1]=p2;
}
else{
    initialisePlayer(p2,Ninja,width-2*BLOCK_WIDTH-30,0);
    players[1]=p2;
}
    //Enregistrement des sources d'evenements
al_register_event_source(event_queue,al_get_display_event_source(display));
al_register_event_source(event_queue, al_get_timer_event_source(timer));
al_register_event_source(event_queue, al_get_keyboard_event_source());
al_register_event_source(event_queue,al_get_joystick_event_source());
al_start_timer(timer);

al_flip_display();

    //Gestion du jeu
while(!done)
{
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
        break;
    }
        //traitement des évènements du controller
    if(ev.type==ALLEGRO_EVENT_JOYSTICK_AXIS ||
        ev.type==ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN ||
        ev.type==ALLEGRO_EVENT_JOYSTICK_BUTTON_UP){
        xc_update(ev,xc);
}
            //Analyse des touches appuyées
            //si une touche de mouvement est appuyée, on remet les frames à 0
            //on enregistre la direction
            //et on informe que l'on veut se déplacer avec isMoving
            //Si la touche est espace alors on met juste en mémoire que la touche a été appuyée

if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
{
    switch(ev.keyboard.keycode)
    {
        case ALLEGRO_KEY_ESCAPE:
        return 1;
        break;
        case ALLEGRO_KEY_LEFT:
        key[KEY_LEFT]=true;
        IsP1Moving1=true;
        p1->orientation=west;
        break;
        case ALLEGRO_KEY_RIGHT:
        key[KEY_RIGTH]=true;
        IsP1Moving2=true;
        p1->orientation=east;
        break;
        case ALLEGRO_KEY_UP:
        key[KEY_UP]=true;
        IsP1Moving3=true;
        p1->orientation=north;
        break;
        case ALLEGRO_KEY_DOWN:
        key[KEY_DOWN]=true;
        IsP1Moving4=true;
        p1->orientation=south;
        break;
        case ALLEGRO_KEY_SPACE:
        key[SPACE]=true;
        break;
        case ALLEGRO_KEY_ENTER:
        key[KEY_ENTER]=true;
        break;
    }
    if(IsP1Moving4 || IsP1Moving1 || IsP1Moving3 || IsP1Moving2){
        IsP1Moving=true;
    }
}
            //Analyse des touches relachés
            //si une touche est relaché, on arrete de se déplacer
            //si c'est espace, alors on déclenche le fait qu'on veut poser une bombe
else if(ev.type == ALLEGRO_EVENT_KEY_UP)
{
    switch(ev.keyboard.keycode)
    {
        case ALLEGRO_KEY_LEFT:
        key[KEY_LEFT]=false;
        IsP1Moving1=false;
        break;
        case ALLEGRO_KEY_RIGHT:
        key[KEY_RIGTH]=false;
        IsP1Moving2=false;
        break;
        case ALLEGRO_KEY_UP:
        key[KEY_UP]=false;
        IsP1Moving3=false;
        break;
        case ALLEGRO_KEY_DOWN:
        key[KEY_DOWN]=false;
        IsP1Moving4=false;
        break;
        case ALLEGRO_KEY_SPACE:
        key[SPACE]=false;
        Bomb_placed=true;
        break;
        case ALLEGRO_KEY_ENTER:
        key[KEY_ENTER]=false;
        capacityON=true;
        break;
    }
    if(!IsP1Moving4 && !IsP1Moving1 && !IsP1Moving3 && !IsP1Moving2){
        IsP1Moving=false;
    }
}




else if(ev.type == ALLEGRO_EVENT_TIMER)
{
                //gestion des déplacements et donc des collisions
    if(p1->dead==0){

        if((key[KEY_UP]) && p1->y >= -20.0) {

            if(BB_collision(0,p1->x+p1->boundX,p1->y+p1->boundY-p1->speed,p1->width,p1->height, map->contents,Bombes,players,p1)==0){
                if(p1->orientation==north)
                    p1->y -= p1->speed;

            }
        }

        if((key[KEY_DOWN]) && p1->y <= height -BLOCK_HEIGHT) {

            if(BB_collision(0,p1->x+p1->boundX, p1->y+p1->boundY+p1->speed,p1->width,p1->height, map->contents,Bombes,players,p1)==0){
                if(p1->orientation==south)
                    p1->y += p1->speed;
            }
        }

        if((key[KEY_LEFT]) && p1->x >= 2.0) {

            if(BB_collision(0,p1->x+p1->boundX-p1->speed, p1->y+p1->boundY,p1->width,p1->height, map->contents,Bombes,players,p1)==0){
                if(p1->orientation==west)
                    p1->x -= p1->speed;
            }
        }

        if((key[KEY_RIGTH]) && p1->x <= width - al_get_bitmap_width(dwarfWaitingEast[DwarfCurFrameWaiting]) - 2.0) {

            if(BB_collision(0,p1->x+p1->boundX+p1->speed,p1->y+p1->boundY,p1->width,p1->height, map->contents,Bombes,players,p1)==0){
                if(p1->orientation==east)
                    p1->x += p1->speed;

            }
        }
        if(Bomb_placed){
            Bomb_placed=false;
            placeBomb(p1,Bombes,map->contents,width,height,0,players);

        }
    }
    if(p2->dead==0){

        if(xc->dpad_x>0.1){

            if(BB_collision(1,p2->x+p2->boundX+p2->speed,p2->y+p2->boundY,p2->width,p2->height, map->contents,Bombes,players,p2)==0){
                p2->orientation=east;
                p2->x+=p2->speed;
                IsP2Moving1=true;
            }
        }
        else if(xc->dpad_x<-0.1){
            if(BB_collision(1,p2->x+p2->boundX-p2->speed, p2->y+p2->boundY,p2->width,p2->height, map->contents,Bombes,players,p2)==0){
                p2->orientation=west;
                p2->x-=p2->speed;
                IsP2Moving1=true;
            }
        }
        else IsP2Moving1=false;

        if(xc->dpad_y>0.1){
            if(BB_collision(1,p2->x+p2->boundX, p2->y+p2->boundY+p2->speed,p2->width,p2->height, map->contents,Bombes,players,p2)==0){
                p2->orientation=south;
                p2->y+=p2->speed;
                IsP2Moving2=true;
            }
        }
        else if(xc->dpad_y<-0.1){
            if(BB_collision(1,p2->x+p2->boundX,p2->y+p2->boundY-p2->speed,p2->width,p2->height, map->contents,Bombes,players,p2)==0){
                p2->orientation=north;
                p2->y-=p2->speed;
                IsP2Moving2=true;
            }
        }
        else IsP2Moving2=false;
        if(IsP2Moving2 || IsP2Moving1){
            IsP2Moving=true;
        }
        else if( !IsP2Moving2 && !IsP2Moving1){
            IsP2Moving=false;
        }
            //Activation de la compétence spéciale
        if(xc->button_y){
            p2->spe.active=1;
        }
        if(xc->button_a){
            p2Bomb=true;
        }
        if(p2Bomb && !xc->button_a){
            p2Bomb=false;
            placeBomb(p2,Bombes,map->contents,width,height,1,players);
        }
    }
    if(capacityON){
        capacityON=false;
        p1->spe.active=1;
    }


        //gestion des frames pour le blackDwarf
    if(++DwarfFrameCountWait >= frameDelay)
    {
        if(++DwarfCurFrameWaiting >= DwarfmaxFrameWait)
            DwarfCurFrameWaiting = 0;

        DwarfFrameCountWait= 0;
    }
    if(++DwarfFrameCountWalk >= frameDelay){
        if(++DwarfCurFrameWalking >= DwarfmaxFrameWalk)
            DwarfCurFrameWalking=0;
        DwarfFrameCountWalk=0;
    }

        //gestion des frames pour le flying soul
    if(++SoulFrameCount >= frameDelay)
    {
        if(++SoulCurFrame >= SoulMaxFrame)
            SoulCurFrame = 0;

        SoulFrameCount= 0;
    }
    //gestion du ninja
    if(++NinjaFrameCount >= frameDelay)
    {
        if(++NinjaCurFrame >= NinjaMaxFrame)
            NinjaCurFrame = 0;

        NinjaFrameCount= 0;
    }

    redraw=true;
}

if(redraw && al_is_event_queue_empty(event_queue)) {
    al_draw_bitmap(doge,0,0,0);
//on trace les murs
    for (i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(map->contents[i][j]->inde==0){
                al_draw_bitmap(block[0],map->contents[i][j]->boundX,map->contents[i][j]->boundY,0);
            }
            else if (map->contents[i][j]->inde==1){
                al_draw_bitmap(block[1],map->contents[i][j]->boundX,map->contents[i][j]->boundY,0);
            }
            else{
                if(map->contents[i][j]->displayBonus==1){
                    switch(map->contents[i][j]->bonusType){
                        case Speed:
                        al_draw_bitmap(bonus[2],map->contents[i][j]->boundX,map->contents[i][j]->boundY,0);
                        break;
                        case Strength:
                        al_draw_bitmap(bonus[1],map->contents[i][j]->boundX,map->contents[i][j]->boundY,0);
                        break;
                        case Capacity:
                        al_draw_bitmap(bonus[0],map->contents[i][j]->boundX,map->contents[i][j]->boundY,0);
                        break;
                    }
                }
            }
        }
    }
//on trace le joueur 1
    if(p1->dead == 0){
            if(p1->character==BlackDwarf)//si le jouer 1 utilise le dwarf
            { 
                if(IsP1Moving==false){
                    switch(p1->orientation){
                        case east:
                        al_draw_bitmap(dwarfWaitingEast[DwarfCurFrameWaiting], p1->x, p1->y, 0);
                        break;
                        case north:
                        al_draw_bitmap(dwarfWaitingNorth[DwarfCurFrameWaiting], p1->x, p1->y, 0);
                        break;
                        case west:
                        al_draw_bitmap(dwarfWaitingWest[DwarfCurFrameWaiting], p1->x, p1->y, 0);
                        break;
                        case south:
                        al_draw_bitmap(dwarfWaitingSouth[DwarfCurFrameWaiting], p1->x, p1->y, 0);
                        break;
                    }

                }
                else if (IsP1Moving==true){
                    if(p1->spe.active){ //on fait courir le nain si sa capacité est active

                        if(p1->orientation==north){
                            al_draw_bitmap(dwarfRunningNorth[DwarfCurFrameWalking], p1->x, p1->y, 0);
                            p1->orientation=north;
                        }
                        else if(p1->orientation==east){
                            al_draw_bitmap(dwarfRunningEast[DwarfCurFrameWalking], p1->x, p1->y, 0);
                            p1->orientation=east;
                        }
                        else if(p1->orientation==west){
                            al_draw_bitmap(dwarfRunningWest[DwarfCurFrameWalking], p1->x, p1->y, 0);
                            p1->orientation=west;
                        }
                        else{
                            al_draw_bitmap(dwarfRunningSouth[DwarfCurFrameWalking], p1->x, p1->y, 0);
                            p1->orientation=south;
                        }
                    }
                    else{

                        if(p1->orientation==north){
                            al_draw_bitmap(dwarfMovingNorth[DwarfCurFrameWalking], p1->x, p1->y, 0);
                            p1->orientation=north;
                        }
                        else if(p1->orientation==east){
                            al_draw_bitmap(dwarfMovingEast[DwarfCurFrameWalking], p1->x, p1->y, 0);
                            p1->orientation=east;
                        }
                        else if(p1->orientation==west){
                            al_draw_bitmap(dwarfMovingWest[DwarfCurFrameWalking], p1->x, p1->y, 0);
                            p1->orientation=west;
                        }
                        else{
                            al_draw_bitmap(dwarfMovingSouth[DwarfCurFrameWalking], p1->x, p1->y, 0);
                            p1->orientation=south;
                        }
                    }
                }
                
            }
            else if (p1->character==FlyingSoul){ //s'il utilise la Flying Soul
                switch(p1->orientation){
                    case north:
                    al_draw_bitmap(soulNorth[SoulCurFrame],p1->x,p1->y,0);
                    break;
                    case south:
                    al_draw_bitmap(soulSouth[SoulCurFrame],p1->x,p1->y,0);
                    break;
                    case east:
                    al_draw_bitmap(soulEast[SoulCurFrame],p1->x,p1->y,0);
                    break;
                    case west:
                    al_draw_bitmap(soulWest[SoulCurFrame],p1->x,p1->y,0);
                    break;
                }
            }
            else if(p1->character==Ninja){
                switch(p1->orientation){

                    case north:
                    al_draw_bitmap(ninjaNorth[NinjaCurFrame],p1->x,p1->y,0);
                    break;
                    case south:
                    al_draw_bitmap(ninjaSouth[NinjaCurFrame],p1->x,p1->y,0);
                    break;
                    case east:
                    al_draw_bitmap(ninjaEast[NinjaCurFrame],p1->x,p1->y,0);
                    break;
                    case west: 
                    al_draw_bitmap(ninjaWest[NinjaCurFrame],p1->x,p1->y,0);
                    break;
                }
            }
        }
        //on trace le joueur 2
        if(p2->dead == 0){
            if(p2->character==FlyingSoul){
                switch(p2->orientation){
                    case north:
                    al_draw_bitmap(soulNorth[SoulCurFrame],p2->x,p2->y,0);
                    break;
                    case south:
                    al_draw_bitmap(soulSouth[SoulCurFrame],p2->x,p2->y,0);
                    break;
                    case east:
                    al_draw_bitmap(soulEast[SoulCurFrame],p2->x,p2->y,0);
                    break;
                    case west:
                    al_draw_bitmap(soulWest[SoulCurFrame],p2->x,p2->y,0);
                    break;
                }
                
            }
            else if(p2->character==BlackDwarf){//s'il utilise le BlackDwarf
                if(IsP2Moving==false){
                    switch(p2->orientation){
                        case east:
                        al_draw_bitmap(dwarfWaitingEast[DwarfCurFrameWaiting], p2->x, p2->y, 0);
                        break;
                        case north:
                        al_draw_bitmap(dwarfWaitingNorth[DwarfCurFrameWaiting], p2->x, p2->y, 0);
                        break;
                        case west:
                        al_draw_bitmap(dwarfWaitingWest[DwarfCurFrameWaiting], p2->x, p2->y, 0);
                        break;
                        case south:
                        al_draw_bitmap(dwarfWaitingSouth[DwarfCurFrameWaiting], p2->x, p2->y, 0);
                        break;
                    }
                }
                else if (IsP2Moving==true){
                    if(p2->spe.active){

                        if(p2->orientation==north){
                            al_draw_bitmap(dwarfRunningNorth[DwarfCurFrameWalking], p2->x, p2->y, 0);
                            p2->orientation=north;
                        }
                        else if(p2->orientation==east){
                            al_draw_bitmap(dwarfRunningEast[DwarfCurFrameWalking], p2->x, p2->y, 0);
                            p2->orientation=east;
                        }
                        else if(p2->orientation==west){
                            al_draw_bitmap(dwarfRunningWest[DwarfCurFrameWalking], p2->x, p2->y, 0);
                            p2->orientation=west;
                        }
                        else{
                            al_draw_bitmap(dwarfRunningSouth[DwarfCurFrameWalking], p2->x, p2->y, 0);
                            p2->orientation=south;
                        }
                    }
                    if(p2->orientation==north){
                        al_draw_bitmap(dwarfMovingNorth[DwarfCurFrameWalking], p2->x, p2->y, 0);
                        p2->orientation=north;
                    }
                    else if(p2->orientation==east){
                        al_draw_bitmap(dwarfMovingEast[DwarfCurFrameWalking], p2->x, p2->y, 0);
                        p2->orientation=east;
                    }
                    else if(p2->orientation==west){
                        al_draw_bitmap(dwarfMovingWest[DwarfCurFrameWalking], p2->x, p2->y, 0);
                        p2->orientation=west;
                    }
                    else{
                        al_draw_bitmap(dwarfMovingSouth[DwarfCurFrameWalking], p2->x, p2->y, 0);
                        p2->orientation=south;
                    }
                }
            }
            else if(p2->character==Ninja){
                switch(p2->orientation){
                    case east:
                    al_draw_bitmap(ninjaEast[DwarfCurFrameWaiting], p2->x, p2->y, 0);
                    break;
                    case north:
                    al_draw_bitmap(ninjaNorth[DwarfCurFrameWaiting], p2->x, p2->y, 0);
                    break;
                    case west:
                    al_draw_bitmap(ninjaWest[DwarfCurFrameWaiting], p2->x, p2->y, 0);
                    break;
                    case south:
                    al_draw_bitmap(ninjaSouth[DwarfCurFrameWaiting], p2->x, p2->y, 0);
                    break;
                }
            }
        }
        
                //on trace les bombes
        for ( i =0;i<8;i++){
            //si la bombe est active et le joueur a qui elle appartient vivant
            if(Bombes[i]->active==1 && ((i<4 && p1->dead == 0) || (i>3 && p2->dead == 0))){

                al_draw_bitmap(bomb[bomb_frame],Bombes[i]->x,Bombes[i]->y,0);
                bomb_frame++;
                if(bomb_frame>15) bomb_frame=0;
                Bombes[i]->explosionTimer--;
                if(Bombes[i]->explosionTimer<=0){
                    trigger(Bombes[i],0);
                    if(i<4){                        
                        explosion(*Bombes[i],i,p1,p1,p2, map, Bombes);                                                                                                                     
                    }
                    else{
                        explosion(*Bombes[i],i,p2,p1,p2, map, Bombes);
                    }
                    Bombes[i]->flaming=10;
                    p1->bombesPosees--;
                }
            }
            //gestion des flammes
            if(Bombes[i]->flaming>0 && Bombes[i]->active==0){ //si la bombe a des flammes à faire, et inactive (donc déjà explosée)
                Bombes[i]->flaming--;
                int strength=0;
                
                x=Bombes[i]->x;
                x=x/BLOCK_WIDTH;
                y=Bombes[i]->y;
                y=y/BLOCK_HEIGHT;
                int BombX,BombY;
                BombX=map->contents[x][y]->boundX;
                BombY=map->contents[x][y]->boundY;
                //on cherche à quel joueur elle appartient
                if(i<4){
                    strength=p1->strength;
                }
                else{
                    strength=p2->strength;
                }
                //on trace autant de flamme que le joueur a de puissance
                for(j = 1;j<strength;j++){
                    //vérification pour savoir si un mur indestructible est sur le chemin
                    if(hasIndeRight==-1 || hasIndeLeft==-1 || hasIndeBottom==-1 || hasIndeTop==-1){
                        if(hasIndeRight==-1 && map->contents[x+j][y]->inde==1){
                            hasIndeRight=j;
                        }
                        if(hasIndeLeft==-1 && map->contents[x-j][y]->inde==1){
                            hasIndeLeft=j;
                        }
                        if(hasIndeBottom==-1 && map->contents[x][y+j]->inde==1){
                            hasIndeBottom=j;
                        }
                        if(hasIndeTop==-1 && map->contents[x][y-j]->inde==1){
                            hasIndeTop=j;
                        }
                    }
                    if(hasIndeRight==-1){

                        al_draw_bitmap(fire_horizontal,BombX+BLOCK_WIDTH*j,BombY,0);

                    }
                    if(hasIndeLeft==-1){

                        al_draw_bitmap(fire_horizontal,BombX-BLOCK_WIDTH*j,BombY,0);        
                    }
                    if(hasIndeBottom==-1){

                        al_draw_bitmap(fire_vertical,BombX,BombY+BLOCK_HEIGHT*j,0);
                    }
                    if(hasIndeTop==-1){

                        al_draw_bitmap(fire_vertical,BombX,BombY-BLOCK_HEIGHT*j,0);     
                    }


                }
                if(hasIndeRight==-1)
                    al_draw_bitmap(fire_end_right,BombX+BLOCK_WIDTH*strength,BombY,0);
                else{
                    al_draw_bitmap(fire_end_right,BombX+BLOCK_WIDTH*(hasIndeRight-1),BombY,0);
                }
                if(hasIndeLeft==-1)
                    al_draw_bitmap(fire_end_left,BombX-BLOCK_WIDTH*strength,BombY,0);   
                else{
                    al_draw_bitmap(fire_end_left,BombX-BLOCK_WIDTH*(hasIndeLeft-1),BombY,0);    

                }
                if(hasIndeBottom==-1)
                    al_draw_bitmap(fire_end_bottom,BombX,BombY+BLOCK_HEIGHT*strength,0);
                else{
                    al_draw_bitmap(fire_end_bottom,BombX,BombY+BLOCK_HEIGHT*(hasIndeBottom-1),0);
                }
                if(hasIndeTop==-1)
                    al_draw_bitmap(fire_end_top,BombX,BombY-BLOCK_HEIGHT*strength,0);   
                else{
                    al_draw_bitmap(fire_end_top,BombX,BombY-BLOCK_HEIGHT*(hasIndeTop-1),0); 
                }
                al_draw_bitmap(fire_cross,BombX,BombY,0);
                hasIndeTop=-1;
                hasIndeBottom=-1;
                hasIndeLeft=-1;
                hasIndeRight=-1;    

            }
        }

        redraw=false;

        //gestion des capacités spéciales
        if(p1->spe.active==1 && !p1->hasUsed){
            if(p1->spe.num==1){
                p1->speed=4;
                p1->spe.capacityTimer--;
                if(p1->spe.capacityTimer<=0){
                    p1->spe.active=0;
                    capacityON=false;
                    p1->speed=2; //après avoir sprintré, le nain est fatigué.
                    p1->hasUsed=1;
                }   
            } else if(p1->spe.num==2){
                p1->spe.capacityTimer--;
                al_draw_bitmap(shield[shieldFrame],p1->x,p1->y,0);
                shieldFrame++;
                if(shieldFrame==31){
                    shieldFrame=0;
                }
                if(p1->spe.capacityTimer<=0){
                    p1->spe.active=0;
                    p1->hasUsed=1;
                }
            }
            else if(p1->spe.num==3){
                p1->spe.capacityTimer--;
                al_draw_bitmap(aura[auraFrame],p1->x,p1->y+15,0);
                al_draw_bitmap(aura[auraFrame],p2->x,p2->y+15,0);
                auraFrame++;
                if(auraFrame>15){
                    auraFrame=0;
                }
                if(p1->spe.capacityTimer<=0){

                    reverse(p1,p2);
                    p1->spe.active=0;
                    p1->hasUsed=1;
                }
            }


        }
        //gestion des capacités spéciales
        if(p2->spe.active==1 && !p2->hasUsed){
            if(p2->spe.num==1){
                p2->speed=4;
                p2->spe.capacityTimer--;
                if(p2->spe.capacityTimer<=0){
                    p2->spe.active=0;
                    capacityON=false;
                    p2->speed=2;
                    p2->hasUsed=1;
                }   
            } else if(p2->spe.num==2){
                p2->spe.capacityTimer--;
                al_draw_bitmap(shield[shieldFrame],p2->x,p2->y,0);
                shieldFrame++;
                if(shieldFrame==31){
                    shieldFrame=0;
                }
                if(p2->spe.capacityTimer<=0){
                    p2->spe.active=0;
                    p2->hasUsed=1;
                }
            }
            else if(p2->spe.num==3){
                p2->spe.capacityTimer--;
                al_draw_bitmap(aura[auraFrame],p1->x,p1->y+15,0);
                al_draw_bitmap(aura[auraFrame],p2->x,p2->y+15,0);
                auraFrame++;
                if(auraFrame>15){
                    auraFrame=0;
                }
                if(p2->spe.capacityTimer<=0){

                    reverse(p1,p2);
                    p1->spe.active=0;
                    p1->hasUsed=1;
                }
            }


        }
        al_flip_display();
    }
    if(p1->dead == 1 || p2->dead == 1){
        done=true;
    }
}
done = false;
event_queue_fin=al_create_event_queue();
al_register_event_source(event_queue_fin,al_get_display_event_source(display));
al_register_event_source(event_queue_fin,al_get_timer_event_source(timer));
al_register_event_source(event_queue_fin,al_get_keyboard_event_source());
al_start_timer(timer);

al_clear_to_color(al_map_rgb(255, 255, 255));
//al_flip_display();

//GESTION DU GAGNANT
while(!done ){


    ALLEGRO_EVENT ev2;
    
    al_wait_for_event(event_queue_fin,&ev2);
    if(ev2.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
        return 1;
    }

    if(ev2.type== ALLEGRO_EVENT_KEY_UP){
        switch(ev2.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
            done=true;
            break;
        }
    }
    else if(ev2.type == ALLEGRO_EVENT_TIMER){
                        //gestion des frames pour le blackDwarf
        if(++DwarfFrameCountWait >= frameDelay)
        {
            if(++DwarfCurFrameWaiting >= DwarfmaxFrameWait)
                DwarfCurFrameWaiting = 0;

            DwarfFrameCountWait= 0;
        }


            //gestion des frames pour le flying soul
        if(++SoulFrameCount >= frameDelay)
        {
            if(++SoulCurFrame >= SoulMaxFrame)
                SoulCurFrame = 0;

            SoulFrameCount= 0;
        }
        redraw=true;
    }
    if(redraw && al_is_event_queue_empty(event_queue_fin)) 
    {
        al_clear_to_color(al_map_rgb(255, 255, 255));
        if(p1->dead ==1)
        {
            if(p2->character == BlackDwarf)
            {
                al_draw_bitmap(dwarfWaitingSouth[DwarfCurFrameWaiting],350, 260, 0);
                
            } else 
            {
                al_draw_bitmap(soulSouth[SoulCurFrame],350,250,0);
                SoulCurFrame++;
                if(SoulCurFrame>=SoulMaxFrame){
                    SoulCurFrame=0;
                }
            }
        }
        else if(p2->dead ==1)
        {
            if(p1->character == BlackDwarf)
            {
                al_draw_bitmap(dwarfWaitingSouth[DwarfCurFrameWaiting],350, 260, 0);
                DwarfCurFrameWaiting++;
                if (DwarfCurFrameWaiting>=DwarfmaxFrameWait)
                {
                    DwarfCurFrameWaiting=0;
                }
            } else
            {
                al_draw_bitmap(soulSouth[SoulCurFrame],350,250,0);
                SoulCurFrame++;
                if(SoulCurFrame>=SoulMaxFrame){
                    SoulCurFrame=0;
                }
            }
            redraw=false;
        } 
        al_draw_bitmap(winner,325,400,0);
        al_flip_display();
    }
}

al_flip_display();
//LIBERATION DE LA MEMOIRE
for(i = 0; i < SoulMaxFrame; i++){
    if(i<DwarfmaxFrameWait){
        al_destroy_bitmap(dwarfWaitingEast[i]);
        al_destroy_bitmap(dwarfWaitingWest[i]);
        al_destroy_bitmap(dwarfWaitingNorth[i]);
        al_destroy_bitmap(dwarfWaitingSouth[i]);
        if (i < DwarfmaxFrameWalk){
            al_destroy_bitmap(dwarfMovingEast[i]);
            al_destroy_bitmap(dwarfMovingWest[i]);
            al_destroy_bitmap(dwarfMovingNorth[i]);
            al_destroy_bitmap(dwarfMovingSouth[i]);
        }
    }
    if(i<8){
        free(Bombes[i]);
    }
    al_destroy_bitmap(soulSouth[i]);
    al_destroy_bitmap(soulWest[i]);
    al_destroy_bitmap(soulEast[i]);
    al_destroy_bitmap(soulNorth[i]);
    al_destroy_bitmap(bomb[i]);
}

al_destroy_bitmap(block[0]);
al_destroy_bitmap(block[1]);
al_destroy_bitmap(fire_horizontal);
al_destroy_bitmap(fire_vertical);
al_destroy_bitmap(fire_end_left);
al_destroy_bitmap(fire_end_right);
al_destroy_bitmap(fire_end_top);
al_destroy_bitmap(fire_end_bottom);
al_destroy_bitmap(fire_cross);
al_destroy_event_queue(event_queue);
for (i = 0; i < 31; ++i)
{
    al_destroy_bitmap(shield[i]);
}
    al_destroy_display(display);                        //destroy our display object
    free(p1);
    free(p2);
    free(xc);
    

    return 0;
}



int BB_collision(int appelant,int b1_x, int b1_y,int b1_w,int b1_h, Mur *murs[][15],bomb *bombes[],player **players, player *origin)
{

    int i,j;
    int b2_w=BLOCK_WIDTH;
    int b2_h=BLOCK_HEIGHT;
    int bomb_width=bombes[0]->width;
    int player_width;
    int player_height;
    int b2_x;
    int b2_y;

//on pourrait délimiter plus pour ne pas avoir à faire tous les blocs, mais les pc sont suffisament puissants pour
    for (i=0;i<15;i++){
        for(j=0;j<15;j++){
            if(murs[i][j]->inde==1 || murs[i][j]->inde==0){
                b2_x=murs[i][j]->boundX;
                b2_y=murs[i][j]->boundY;
                if ((b1_x < b2_x + b2_w +2) && //le 2 est là pour laisser un peu de jeu
                    (b1_y < b2_y + b2_h +2) && 
                    (b2_x < b1_x + b1_w -2) && 
                    (b2_y < b1_y + b1_h -2))    
                {
        // il y a collision

                    return 1;
                }
            }
            //on regarde si il y a un bonus à ramasser
            if(murs[i][j]->displayBonus==1 && murs[i][j]->inde==2){
                b2_x=murs[i][j]->boundX;
                b2_y=murs[i][j]->boundY;
                if ((b1_x < b2_x + b2_w ) && 
                    (b1_y < b2_y + b2_h ) && 
                    (b2_x < b1_x + b1_w ) && 
                    (b2_y < b1_y + b1_h ))  
                {
                    murs[i][j]->displayBonus=0;
                    switch(murs[i][j]->bonusType){
                        case Speed:
                        if(origin->speed<4)
                            origin->speed++;
                        break;
                        case Strength:

                        origin->strength++;
                        break;
                        case Capacity:
                        if (origin->bombCapacity<=4)
                            origin->bombCapacity++;
                        break;
                    }

                }
            }
        }

        //on teste aussi les bombes
        if (i < 8){
            if(bombes[i]->active==1){

                b2_x=bombes[i]->x;
                b2_y=bombes[i]->y;


                if ((b1_x < b2_x + bomb_width ) && 
                    (b1_y < b2_y + bomb_width ) && 
                    (b2_x < b1_x + b1_w ) && 
                    (b2_y < b1_y + b1_h ))  
                {

                    return 1;
                }
            }
        }
        //on teste les joueurs
        if(i<2 && i!=appelant){
            b2_x=players[i]->x+players[i]->boundX;
            b2_y=players[i]->y+players[i]->boundY;
            player_width=players[i]->width;
            player_height=players[i]->height;
            if ((b1_x < b2_x + player_width ) && 
                (b1_y < b2_y + player_height) && 
                (b2_x < b1_x + b1_w ) && 
                (b2_y < b1_y + b1_h ))  
            {

                return 1;
            }
        }
    }

    // no collision
    return 0;
}

void placeBomb(player *p,bomb *bombs[],Mur *murs[][15],int width,int height,int numplayer,player **players){

    int dir=p->orientation;
    int i;
    int x;
    int y;
    x=p->x+p->boundX+p->width/2;  //on place le repère x vers le milieu du personnage
    x=x/BLOCK_WIDTH;
    y=p->y+p->boundY+p->height/2;
    y=y/BLOCK_HEIGHT;
    int b2_w=BLOCK_WIDTH;
    int b2_h=BLOCK_HEIGHT;
    switch(dir){
        case south:

        if(murs[x][y+1]->inde==2){
            //on test si on peut placer la bombe
            for( i=0;i<2;i++){
                if(i!=numplayer){

                    int b1_x=players[i]->x+players[i]->boundX;
                    int b1_y=players[i]->y+players[i]->boundY;
                    int b1_w=players[i]->width;
                    int b1_h=players[i]->height;
                    if ((b1_x < murs[x][y+1]->boundX + b2_w) && 
                        (b1_y < murs[x][y+1]->boundY + b2_h) && 
                        (murs[x][y+1]->boundX < b1_x + b1_w) && 
                        (murs[x][y+1]->boundY < b1_y + b1_h))   
                    {

                        return;
                    }
                }
            }
                //on cherche la premiere bombe inactive et on l'active
            for (i=0+numplayer*4; i < p->bombCapacity+numplayer*4;i++){
                if(bombs[i]->active==0){
                    bombs[i]->x=murs[x][y+1]->boundX;
                    bombs[i]->y=murs[x][y+1]->boundY+10;

                    trigger(bombs[i],1);
                    p->bombesPosees++;
                    break;
                }
            }
        }
        break;
        case east:

        if(murs[x+1][y]->inde==2){
            for( i=0;i<2;i++){
                if(i!=numplayer){
                    int b1_x=players[i]->x+players[i]->boundX;
                    int b1_y=players[i]->y+players[i]->boundY;
                    int b1_w=players[i]->width;
                    int b1_h=players[i]->height;
                        if ((b1_x < murs[x+1][y]->boundX + b2_w) && //le 2 est là pour laisser un peu de jeu
                            (b1_y < murs[x+1][y]->boundY + b2_h) && 
                            (murs[x+1][y]->boundX < b1_x + b1_w) && 
                            (murs[x+1][y]->boundY < b1_y + b1_h))   
                        {

                            return;
                        }
                    }
                }
                for (i=0+numplayer*4; i < p->bombCapacity+numplayer*4;i++){
                    if(bombs[i]->active==0){

                        bombs[i]->x=murs[x+1][y]->boundX+20;
                        bombs[i]->y=murs[x+1][y]->boundY;

                        trigger(bombs[i],1);
                        p->bombesPosees++;
                        break;
                    }
                }
            }
            break;
        //a finir
            case west:

            if(murs[x-1][y]->inde==2){
                for( i=0;i<2;i++){
                    if(i!=numplayer){
                        int b1_x=players[i]->x+players[i]->boundX;
                        int b1_y=players[i]->y+players[i]->boundY;
                        int b1_w=players[i]->width;
                        int b1_h=players[i]->height;
                        if ((b1_x < murs[x-1][y]->boundX + b2_w) && //le 2 est là pour laisser un peu de jeu
                            (b1_y < murs[x-1][y]->boundY + b2_h) && 
                            (murs[x-1][y]->boundX < b1_x + b1_w) && 
                            (murs[x-1][y]->boundY < b1_y + b1_h))   
                        {

                            return;
                        }
                    }
                }
                for (i=0+numplayer*4; i < p->bombCapacity+numplayer*4;i++){
                    if(bombs[i]->active==0){

                        bombs[i]->x=murs[x-1][y]->boundX;
                        bombs[i]->y=murs[x-1][y]->boundY;

                        trigger(bombs[i],1);
                        p->bombesPosees++;
                        break;
                    }
                }
            }
            break;
            case north:
            if(murs[x][y-1]->inde==2){
                for( i=0;i<2;i++){
                    if(i!=numplayer){
                        int b1_x=players[i]->x+players[i]->boundX;
                        int b1_y=players[i]->y+players[i]->boundY;
                        int b1_w=players[i]->width;
                        int b1_h=players[i]->height;
                        if ((b1_x < murs[x][y-1]->boundX + b2_w) && //le 2 est là pour laisser un peu de jeu
                            (b1_y < murs[x][y-1]->boundY + b2_h) && 
                            (murs[x][y-1]->boundX < b1_x + b1_w) && 
                            (murs[x][y-1]->boundY < b1_y + b1_h))   
                        {

                            return;
                        }
                    }
                }
                for (i=0+numplayer*4; i < p->bombCapacity+numplayer*4;i++){
                    if(bombs[i]->active==0){

                        bombs[i]->x=murs[x][y-1]->boundX;
                        bombs[i]->y=murs[x][y-1]->boundY;

                        trigger(bombs[i],1);
                        p->bombesPosees++;
                        break;
                    }
                }
            }
            break;
        }
    }
