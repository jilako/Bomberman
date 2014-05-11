#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "sound.h"

void playSound(char *soundName) {
	
	ALLEGRO_SAMPLE *sample = al_load_sample(soundName);

	if(!sample) {
		printf("Audio clip sample not loaded\n");
		exit(EXIT_FAILURE);
	}
	
	al_play_sample(sample, 0.9, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

}

ALLEGRO_SAMPLE *playMainSound(char *soundName) {
	
	ALLEGRO_SAMPLE *sample = NULL;


	sample = al_load_sample(soundName);

	if(!sample) {
		printf("Audio clip sample not loaded\n");
		exit(EXIT_FAILURE);
	}
	al_play_sample(sample, 0.6, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);

	return sample;

}

void stopSound(ALLEGRO_SAMPLE *sample) {
	al_destroy_sample(sample);
}