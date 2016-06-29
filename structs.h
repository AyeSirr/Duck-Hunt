#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
/**
 * \brief Struktura przechowujaca statystyki gry.
 *
 * \param wynik::score ilosc zdobytych punktow przez gracza.
 * \param wynik::health zdrowie gracza.
 */
struct wynik
{
    int score;
    int health;
};
/**
 * \brief Struktura przechowujaca dane przeciwnikow.
 *
 * \param rockets::x wspolrzedna x celu.
 * \param rockets::y wspolrzedna y celu.
 * \param rockets::speed predkosc poruszania sie celu.
 */
struct rockets
{
    int x;
    int y;
    int speed;
};
/**
 * \brief Struktura pojedynczego elementu listy.
 *
 * \param list_node::target informacje o przeciwniku.
 * \param list_node::next wskaznik na nastepny element listy.
 * \param list_node::prev wskaznik na poprzedni element listy.
 */
struct list_node
{
    struct rockets target;
    struct list_node *next, *prev;
};
/**
 * \brief Struktura wartownikow.
 *
 * \param guard::head wskaznik na poczatkowy element listy.
 * \param guard::tail wskaznik na koncowy element listy.
 */
struct guard
{
    struct list_node *head;
    struct list_node *tail;
};
/**
 * \brief Struktura przechowujaca pliki audio, bitmapy i czcionki gry.
 *
 */
struct Bitmaps
{
    ALLEGRO_BITMAP *crosshair;
    ALLEGRO_BITMAP *rocket;
    ALLEGRO_BITMAP *tlo;
    ALLEGRO_BITMAP *tlo2;
    ALLEGRO_BITMAP *gameover;
    ALLEGRO_FONT *font72b;
    ALLEGRO_FONT *font48b;
    ALLEGRO_FONT *font24b;
    ALLEGRO_SAMPLE *Music1;
    ALLEGRO_SAMPLE *Music2;
    ALLEGRO_SAMPLE *shot;
};

struct Bitmaps LoadBitmaps(ALLEGRO_DISPLAY *display);
void Addatlast(struct guard *guardian, struct list_node *new_node);
void removeTarget(struct guard *guardian, struct list_node *elem);

#endif // STRUCTURES_H_INCLUDED

