#include "structs.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
/**
 * \brief Funkcja tworzaca strukture "bitmap", w której sa zapisane wszystkie bitmapy, pliki audio i czcionki potrzebne do uruchomienia gry.
 *
 */
struct Bitmaps LoadBitmaps(ALLEGRO_DISPLAY *display)
{
    struct Bitmaps bitmap;
    bitmap.crosshair = al_load_bitmap("celownik.png");
    bitmap.rocket = al_load_bitmap("rocket.png");
    bitmap.tlo = al_load_bitmap("tlo.png");
    bitmap.tlo2 = al_load_bitmap("tlo2.png");
    bitmap.gameover = al_load_bitmap("gameover.png");
    bitmap.font48b = al_load_font("Amatic-Bold.ttf", 48, 0);
    bitmap.font72b = al_load_font("Amatic-Bold.ttf", 72, 0);
    bitmap.font24b = al_load_font("Amatic-Bold.ttf", 24, 0);
    bitmap.Music1 = al_load_sample("AdventureMeme.ogg");
    bitmap.shot = al_load_sample("shooting.wav");
    bitmap.Music2 = al_load_sample("explos.wav");
    return bitmap;
};
/**
 * \brief Funkcja inicjujaca wyzerowanie wartownikow, potrzebnych do stworzenia listy.
 * \brief Funkcja zawierajaca inicjacje biblioteki allegro - czcionki, audio, bitmapy, timer, itp.
 *
 * \param struct guard *guardian - wskaznik na strukture wartowników.
 */
void createlist(struct guard *guardian)
{
    guardian->head = NULL;
    guardian->tail = NULL;
}
/**
 * \brief Funkcja dodajaca element na koncu listy.
 *
 * \param *guardian - wskaznik na strukture wartowników.
 * \param *new_node - wskaznik na strukture listy dwukierunkowej.
 */
void AddatLast(struct guard *guardian, struct list_node *new_node){
    new_node->next = NULL;
    new_node->prev = NULL;
   if(guardian->head==NULL){
      guardian->tail = new_node;
      guardian->head = new_node;

   }else {
        guardian->tail->next = new_node;
      new_node->prev = guardian->tail;
   }
   guardian->tail = new_node;
}
/**
 * \brief Funkcja usuwajaca element listy, podany poprzez wskaznik na liste dwukierunkowa.
 *
 * \param *guardian - wskaznik na strukture wartowników.
 * \param *new_node - wskaznik na strukture listy dwukierunkowej.
 */
void removeTarget(struct guard *guardian, struct list_node *elem)
{
    if(guardian->head == guardian->tail && guardian->head) {
        guardian->head = NULL;
        guardian->tail = NULL;
    } else if(elem->prev == NULL) {
        guardian->head = elem->next;
        elem->next->prev = NULL;

    } else if(elem->next == NULL) {
        guardian->tail = elem->prev;
        elem->prev->next = NULL;

    } else {
        elem->next->prev = elem->prev;
        elem->prev->next = elem->next;
    }
}


