#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "globals.h"
#include "objects.h"
#include "player.h"
//#include "peace.h"
#include "drugs.h"

int main(void)
{
    //primitive variable
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
    bool isGameOver = false;

    //object variables
    Player player;
    Drug drugs[DrugFreq];
    Peace peace[PeaceFreq];

    //Allegro variables
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font18 = NULL;

    //Initialization Functions
    if(!al_init())										//initialize Allegro
        return -1;

    display = al_create_display(WIDTH, HEIGHT);			//create our display object

    if(!display)										//test display object
        return -1;

    al_init_primitives_addon();
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    srand(time(NULL));
    InitPlayer(player);
    InitDrugnPeace(drugs, DrugFreq, peace);


    font18 = al_load_font("arial.ttf", 18, 0);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            if(keys[SPACE])
            {
                if(player.isRising && (player.y < (HEIGHT*5/8)-25) && (player.y > (HEIGHT/2)-25) && player.firstSpace)
                {
                    player.speed = 7;
                    player.isRising = false;
                    player.firstSpace = false;
                }
                else if(!player.isJumping)
                {
                    player.isJumping = true;
                    player.firstSpace = true;
                }
            }


            if(keys[DOWN])
                if(player.isRising)
                {
                    player.speed = 0;
                }
                else
                {
                    player.speed = -14;
                }


            if(!isGameOver)
            {
                StartDrugnPeace(drugs, DrugFreq, peace);
                UpdateDrugnPeace(drugs, DrugFreq, peace);
                CollideDrugnPeace(drugs, DrugFreq, player, peace);

                if(player.drugs > 4)
                    isGameOver = false;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = true;
                break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = false;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = false;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = false;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = false;
                break;
            case ALLEGRO_KEY_SPACE:
                keys[SPACE] = false;
                break;
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            if(!isGameOver)
            {
                DrawPlayer(player);
                DrawDrugnPeace(drugs, DrugFreq, peace);

                al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has used %i drugs. Player has collected %i good objects", player.drugs, player.peaces);
                al_draw_line(0, HEIGHT*3/4, WIDTH, HEIGHT*3/4, al_map_rgb(0,0,255), 2);
            }
            else
            {
                al_draw_textf(font18, al_map_rgb(0, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i", player.peaces);
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font18);
    al_destroy_display(display);						//destroy our display object

    return 0;
}
