#ifndef sound_h
#define sound_h
void playSound(char *soundName);
ALLEGRO_SAMPLE *playMainSound(char *soundName);
void stopSound(ALLEGRO_SAMPLE *sample);

#endif
