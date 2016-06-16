#include "structures.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

struct Bitmaps LoadBitmaps(ALLEGRO_DISPLAY *display)
{
    struct Bitmaps bitmap;
    bitmap.crosshair = al_load_bitmap("celownik.png");
    bitmap.rocket = al_load_bitmap("rocket.png");
    bitmap.tlo = al_load_bitmap("tlo.png");
    bitmap.tlo2 = al_load_bitmap("tlo2.png");
    bitmap.font48b = al_load_font("Amatic-Bold.ttf", 48, 0);
    bitmap.font72b = al_load_font("Amatic-Bold.ttf", 72, 0);
    return bitmap;
};
void createlist(struct guard *guardian)
{
    guardian->head = NULL;
    guardian->tail = NULL;
}
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
   guardian->ile++;
}
void removeTarget(struct guard *guardian, struct list_node *elem)
{
    guardian->ile--;
  if(elem->prev)
    elem->prev->next = elem->next;
  else
  guardian->head = elem->next;
  if(elem->next)
    elem->next->prev = elem->prev;
  else
  guardian->tail = elem->prev;
  free(elem);

    /*
    struct list_node *elem;

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
*/
}


