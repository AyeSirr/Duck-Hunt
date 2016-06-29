#include "structs.h"
#include "menuu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
/**
 * Szerokosc ekranu okna allegro.
 */
#define ScreenW 800
/**
 * Wysokosc ekranu okna allegro.
 */
#define ScreenH 600
/**
 * Obszar pojawiania sie targetow.
 */
#define spawn (500-70+1)+70
/**
 * \brief Funkcja tworzaca rakiety o okreslonych parametrach na mapie.
 *
 * \param *bitmap wskaznik na strukture bitmap.
 * \param *guardian wskaznik na strukture wartownikow.
 */
void makerockets(struct Bitmaps *bitmap, struct guard *guardian)
{
    struct list_node *node;
    node = (struct list_node*) malloc (sizeof(struct list_node));
        if(node == NULL) {
            printf("malloc ERROR");
        }

     node->target.x = -al_get_bitmap_width(bitmap->rocket);
     node->target.y = rand()%spawn - al_get_bitmap_height(bitmap->rocket);
     node->target.speed = 2.2;
     AddatLast(guardian, node);
}
/**
 * \brief Funkcja wyswietlajaca przeciwnikow na mapie.
 *
 */
void showrockets(struct Bitmaps *bitmap, struct guard *guardian)
{
    struct list_node *buff;
    buff = guardian->head;
    while(buff) {
        al_draw_bitmap(bitmap->rocket, buff->target.x ,buff->target.y ,0);
        buff = buff->next;
    }
}
/**
 * \brief Funkcja pozwalajaca na poruszanie sie przeciwnikow na mapie.
 *
 * \param *guardian wskaznik na strukture wartownikow.
 * \param *scores wskaznik na strukture(wynik) liczaca statystyki punktow i zycia.
 */
void moveTargets(struct guard *guardian, struct wynik *scores)
{
    struct list_node *buff;
    buff = guardian->head;
    while(buff) {
        buff->target.x = buff->target.x + buff->target.speed;
        if(buff->target.x > ScreenW)
            {
                buff->target.x = -100;
                scores->health-=1;
            }
        buff = buff->next;
    }

}
/**
 * \brief Funkcja zwracajaca aktualny czas w milisekundach, wykorzystano biblioteke time.h.
 *
 */
long long GiveTimeInMiliseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long Miliseconds = tv.tv_sec*1000LL + tv.tv_usec/1000;
    return Miliseconds;
}
/**
 * \brief Funkcja odpowiedzialna strzelanie/niszczenie rakiet na podstawie polozenia x i y.
 *
 * \param *guardian wskaznik na strukture wartownikow.
 * \param *scores wskaznik na strukture(wynik) liczaca statystyki zdobytych punktow i zycia.
 * \param x wspolrzedna x myszki.
 * \param y wspolrzedna y myszki.
 */
void shots(struct Bitmaps *bitmap, struct guard *guardian, int x, int y, struct wynik *scores)
{
    int Width = al_get_bitmap_width(bitmap->rocket);
    int Height = al_get_bitmap_height(bitmap->rocket);
    struct list_node *buff;
     buff = guardian->head;
        while(buff) {
      if((buff->target.x + Width) > x && buff->target.x < x &&  (buff->target.y + Height) > y && buff->target.y < y  )
        {
            removeTarget(guardian, buff);
            scores->score+=5;
        }
        buff = buff->next;
        }
}
/**
 * \brief Funkcja zapisujaca wyniki do pliku.
 *
 */
 void savetofile(int score)
 {
     FILE *plik;
     plik = fopen("wyniki.txt", "a+");
     char imie[50];
     printf("Podaj nick \n");
     scanf("%s", imie);
     fprintf(plik, " %s  %d \n", imie, score);
     fclose(plik);
 }
 /**
 * \brief Funkcja odczytujaca wyniki z pliku.
 *
 */
 void odczyt()
{
    FILE *plik;
     plik = fopen("wyniki.txt", "r");
     char bufor[50];
     printf("Ranking: \n");
     while(feof(plik)==0)
    {
     fgets(bufor, 512, plik);
     printf("%s", bufor);
    }
    fclose(plik);
}
/**
 * \brief Funkcja odpowiedzialna za glowne uruchomienie gry.
 *
 */
void GotoGame(struct Bitmaps bitmap, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, ALLEGRO_DISPLAY *display) {

    bool check = false;
    int pos_x, pos_y;
    srand(time(NULL));
    al_reserve_samples(20);
    struct wynik scores;
    scores.score = 0;
    scores.health = 5;
    struct guard *guardian = (struct guard*) malloc(sizeof(struct guard));
    createlist(guardian);
    double time = al_get_time();
    long long lastTargetTime = 0;
    while(!check)
    {
        if(lastTargetTime+500 < GiveTimeInMiliseconds()) {
            makerockets(&bitmap, guardian);
            lastTargetTime = GiveTimeInMiliseconds();
        }



        if ( al_get_time() > time + 0.0001)
        {
            moveTargets(guardian, &scores);
            time = al_get_time();
        }

        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);


        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;

        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            al_play_sample(bitmap.shot, 0.4, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
             shots(&bitmap, guardian, ev.mouse.x, ev.mouse.y, &scores);
            }

        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
            check=true;
            }
        al_draw_bitmap(bitmap.tlo, 0, 0,0);
        showrockets(&bitmap, guardian);
        al_draw_textf(bitmap.font48b, al_map_rgb(0,0,0), 500, 525, ALLEGRO_ALIGN_CENTER, "SCORE:  %d", scores.score);
        al_draw_textf(bitmap.font48b, al_map_rgb(0,0,0), 300, 525, ALLEGRO_ALIGN_CENTER, "HEALTH:  %d", scores.health);
        int score = scores.score;
        al_draw_bitmap(bitmap.crosshair, pos_x-20,pos_y-20,0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,150,0));
        if(scores.health < 1)
            {
                check=true;
            al_play_sample(bitmap.Music2, 0.4, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            al_draw_bitmap(bitmap.gameover, 0, 0,0);
            al_draw_textf(bitmap.font48b, al_map_rgb(0,200,0), 400, 250, ALLEGRO_ALIGN_RIGHT, "YOUR SCORE:  %d", scores.score);
            al_flip_display();
            al_rest(5.0);
            savetofile(score);
            odczyt();
            GotoMenu(bitmap, eventQueue, display, timer);
            }
}
}
