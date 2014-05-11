animation.o: map.o player.o bomb.o xc.o sound.o bitmap_template.o
	gcc -Wall map.o player.o bomb.o xc.o sound.o bitmap_template.o `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0` -o animation

map.o: map.c
	gcc -c -Wall map.c
player.o: player.c map.c
	gcc -c -Wall player.c map.c
bomb.o: bomb.c
	gcc -c -Wall bomb.c
xc.o: xc.c
	gcc -c -Wall xc.c `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
bitmap_template.o: bitmap_template.c
	gcc -c -Wall bitmap_template.c `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
sound.o: sound.c
	gcc -c -Wall sound.c `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0`
clean:
	rm *.o