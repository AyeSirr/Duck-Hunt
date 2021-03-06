#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "structures.h"

void GotoGame(struct Bitmaps bitmap, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, ALLEGRO_DISPLAY *display);
void makerockets(struct Bitmaps *bitmap, struct guard *guardian);
void showrockets(struct Bitmaps *bitmap, struct guard *guardian);
void moveTargets(struct guard *guardian, struct wynik *score);
void shot(struct Bitmaps *bitmap, struct guard *guardian, int x, int y, struct wynik *score);
void savetofile(int score);
void odczyt();


#endif // GAME_H_INCLUDED
