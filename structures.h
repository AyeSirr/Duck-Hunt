#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
struct rockets
{
    bool live;
    int x;
    int y;
    int speed;
};
struct list_node
{
    int data;
    struct rockets target;
    struct list_node *next, *prev;
};
struct guard
{
    int ile;
    struct list_node *head;
    struct list_node *tail;
};
struct Bitmaps
{
    ALLEGRO_BITMAP *crosshair;
    ALLEGRO_BITMAP *rocket;
    ALLEGRO_BITMAP *tlo;
    ALLEGRO_BITMAP *tlo2;
    ALLEGRO_FONT *font72b;
    ALLEGRO_FONT *font48b;
};

struct Bitmaps LoadBitmaps(ALLEGRO_DISPLAY *display);
void Addatlast(struct rockets target, struct list_node *new_node);
void removeTarget(struct guard *guardian, struct list_node *elem);
struct list_node *nextelements();

#endif // STRUCTURES_H_INCLUDED

