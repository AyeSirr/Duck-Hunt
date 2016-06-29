#include "structs.h"
#include "menuu.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#define ScreenW 800
#define ScreenH 600
/**
 * Wspólrzedne pola rozpoczynajacego gre.
 */
#define start posx < 490 && posx > 315 && posy < 230 && posy > 175
/**
 * Wspólrzedne pola zamykajacego gre.
 */
#define exitx posx < 420 && posx > 380 && posy < 472 && posy > 435
/**
 * Wspólrzedne pola pokazujacego ranking.
 */
#define ranking posx < 450 && posx > 350 && posy < 315 && posy > 280
/**
 * \brief Funkcja zwracajaca na podstawie pozycji kursora wartosc, która bedzie uzywana do wyboru opcji gry.
 *
 */
int Option(int posx, int posy)
{
    if(start)
    {
        return 1;
    }
    if(exitx)
    {
        return 2;
    }
    if(ranking)
    {
        return 3;
    }
}

/**
 * \brief Funkcja uruchamiajaca menu gry.
 *
 */
void GotoMenu(struct Bitmaps bitmap, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_DISPLAY *display,  ALLEGRO_TIMER *timer)
{
    bool check = false;
    int posx, posy;

    while(!check)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);
        al_draw_bitmap(bitmap.tlo2, 0, 0, 0);
        al_draw_text(bitmap.font72b, al_map_rgb(150,0,0), ScreenW/2, ScreenH/4.5, ALLEGRO_ALIGN_CENTER, "NEW GAME");
        al_draw_text(bitmap.font48b, al_map_rgb(150,0,0), ScreenW/2, ScreenH/2.5, ALLEGRO_ALIGN_CENTER, "RANKING");
        al_draw_text(bitmap.font48b, al_map_rgb(150,0,0), ScreenW/2, ScreenH/1.4, ALLEGRO_ALIGN_CENTER, "END");
        al_play_sample(bitmap.Music1, 0.4, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			check = true;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			posx = ev.mouse.x;
			posy = ev.mouse.y;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
                if(Option(posx,posy)==1){
                    check = true;
                    al_stop_samples();
                    GotoGame(bitmap, eventQueue, timer, display);}
                    if(Option(posx,posy)==2)
                    check = true;
                    if(Option(posx,posy)==3){
                    odczyt();}


		}
          al_draw_bitmap(bitmap.crosshair, posx-20,posy-20,0);

            al_flip_display();
            al_clear_to_color(al_map_rgb(255,255,255));
    }
}

