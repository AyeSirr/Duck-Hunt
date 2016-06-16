#include "structures.h"
#include "menuu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define ScreenW 800
#define ScreenH 600
#define spawnArea (430-80+1)+80

void makerockets(struct Bitmaps *bitmap, struct guard *guardian)
{

    struct list_node *node;

    //struct list_node lista;

        node = (struct list_node*) malloc (sizeof(struct list_node));
        if(node == NULL) {
            printf("malloc ERROR");
        }

     node->target.x = -al_get_bitmap_width(bitmap->rocket);
     node->target.y = rand()%spawnArea - al_get_bitmap_height(bitmap->rocket);
     node->target.speed = 1.8;
     AddatLast(guardian, node);

}

void showrockets(struct Bitmaps *bitmap, struct guard *guardian)
{
    struct list_node *buff;
    buff = guardian->head;
    while(buff) {
        al_draw_bitmap(bitmap->rocket, buff->target.x ,buff->target.y ,0);
        buff = buff->next;
    }
}

void moveTargets(struct guard *guardian)
{
    struct list_node *buff;
    buff = guardian->head;
    while(buff) {
        buff->target.x = buff->target.x + buff->target.speed;
        buff = buff->next;
    }

}

long long currentTimestamp() {
    struct timeval te;
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

void shots(struct Bitmaps *bitmap, struct guard *guardian, int x, int y) {

    int Width = al_get_bitmap_width(bitmap->rocket);
    int Height = al_get_bitmap_height(bitmap->rocket);
    struct list_node *node;
     node = guardian->head;
        while(node!=NULL) {
      if(node->target.x < x && (node->target.x + Width) > x && node->target.y < y && (node->target.y + Height) > y )
        {
        removeTarget(guardian, node);
        }
        node = node->next;
        }

}

void GotoGame(struct Bitmaps bitmap, ALLEGRO_EVENT_QUEUE *eventQueue, ALLEGRO_TIMER *timer, ALLEGRO_DISPLAY *display) {

    bool check = false;
    int pos_x, pos_y;
    srand(time(NULL));


    struct guard *guardian = (struct guard*) malloc(sizeof(struct guard));
    createlist(guardian);
    float elapsedTime= al_get_time();
    double time = al_get_time();

    long long lastTargetTime = 0;
    while(!check)
    {


        int i;
        if(lastTargetTime+2000 < currentTimestamp()) {
            makerockets(&bitmap, guardian);
            lastTargetTime = currentTimestamp();
            printf("dodaje rakiete \n");
        }



        if ( al_get_time() > time + 0.0001)
        {
            moveTargets(guardian);
            time = al_get_time();
        }

        ALLEGRO_EVENT ev;
        al_wait_for_event(eventQueue, &ev);


        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            pos_x = ev.mouse.x;
            pos_y = ev.mouse.y;

        } else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
             shots(&bitmap, &guardian, pos_x, pos_y);
            }

        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
            check=true;
            exit(1);
            }

        al_draw_bitmap(bitmap.tlo, 0, 0,0);
        showrockets(&bitmap, guardian);
        al_draw_bitmap(bitmap.crosshair, pos_x-20,pos_y-20,0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,150,0));

    }
}
