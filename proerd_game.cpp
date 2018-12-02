#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "objects.h"

//GLOBALS==============================
const int WIDTH = 800;
const int HEIGHT = 400;
const int NUM_COMETS = 10;
enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};

//prototypes
void InitPlayer(Player &player);
void DrawPlayer(Player &player);

void InitDrug(Drug drugs[], int size);
void DrawDrug(Drug drugs[], int size);
void StartDrug(Drug drugs[], int size);
void UpdateDrug(Drug drugs[], int size);
void CollideDrug(Drug drugs[], int cSize, Player &player);

int main(void)
{
    //primitive variable
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
    bool isGameOver = false;

    //object variables
    Player player;
    Drug drugs[NUM_COMETS];

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
    InitDrug(drugs, NUM_COMETS);

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
                StartDrug(drugs, NUM_COMETS);
                UpdateDrug(drugs, NUM_COMETS);
                CollideDrug(drugs, NUM_COMETS, player);

                if(player.lives <= 0)
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
                DrawDrug(drugs, NUM_COMETS);

                al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has %i lives left. Player has destroyed %i objects", player.lives, player.score);
                al_draw_line(0, HEIGHT*3/4, WIDTH, HEIGHT*3/4, al_map_rgb(0,0,255), 2);
            }
            else
            {
                al_draw_textf(font18, al_map_rgb(0, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i", player.score);
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

void InitPlayer(Player &player)
{
    player.x = WIDTH/4;
    player.y = (HEIGHT*3/4)-25;
    player.ID = PLAYER;
    player.lives = 3;
    player.speed = 7;
    player.boundx = 25;
    player.boundy = 25;
    player.score = 0;
    player.isJumping = false;
    player.gravity = 0.2;
    player.isRising = false;
    player.firstSpace = false;
}
void DrawPlayer(Player &player)
{
    //LÓGICA DO PULO COM GRAVIDADE
    if(player.isJumping)
    {
        player.y -= player.speed;
        player.speed -= player.gravity;

        if(player.speed > 0 && (player.y < (HEIGHT*3/4)-25))
        {
            player.isRising = true;
        }
        else
        {
            player.isRising = false;
        }
    }
    if(keys[DOWN] && player.y >= (HEIGHT*3/4)-25)
    {
        player.y = (HEIGHT*3/4)-20;
        player.boundy = 20;
        al_draw_filled_rectangle(player.x-25, player.y - 20, player.x + 25, player.y + 20, al_map_rgb(0, 255, 0));
    }
    else if (player.y >= (HEIGHT*3/4)-25)
    {
        player.y = (HEIGHT*3/4)-25;
        player.boundy = 25;
        player.speed = 7;
        player.isJumping = false;
        player.firstSpace = false;
        al_draw_filled_rectangle(player.x-25, player.y - 25, player.x + 25, player.y + 25, al_map_rgb(0, 255, 0));
    }
    else
    {
        player.boundy = 25;
        al_draw_filled_rectangle(player.x-25, player.y - 25, player.x + 25, player.y + 25, al_map_rgb(0, 255, 0));
    }
}

void InitDrug(Drug drugs[], int size)
{
    for(int i = 0; i < size; i++)
    {
        drugs[i].ID = ENEMY;
        drugs[i].live = false;
        drugs[i].speed = 5;
        drugs[i].boundx = 25;
        drugs[i].boundy = 25;
    }
}
void DrawDrug(Drug drugs[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(drugs[i].live)
        {
            if(drugs[i].boundy == 50)
            {
                al_draw_filled_rectangle(drugs[i].x - 25, drugs[i].y - 50, drugs[i].x + 25, drugs[i].y + 50, al_map_rgb(255, 0, 0));
            }
            else
            {
                al_draw_filled_rectangle(drugs[i].x - 25, drugs[i].y - 25, drugs[i].x + 25, drugs[i].y + 25, al_map_rgb(255, 0, 0));
            }
        }
    }
}
void StartDrug(Drug drugs[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(!drugs[i].live)
        {
            if(rand() % 750 == 0 && drugs[i].x - drugs[i].boundx > drugs[i-1].x + drugs[i-1].boundx)
            {
                //OBSTÁCULO PEQUENO
                drugs[i].live = true;
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-25;
                drugs[i].boundy = 25;
            }
            else if (rand() % 500 == 0 && drugs[i].x - drugs[i].boundx > drugs[i-1].x + drugs[i-1].boundx)
            {
                //OBSTÁCULO FLUTUANTE
                drugs[i].live = true;
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-100;
                drugs[i].boundy = 25;
            }
            else if (rand() % 250 == 0 && drugs[i].x - drugs[i].boundx > drugs[i-1].x + drugs[i-1].boundx)
            {
                //OBSTÁCULO GRANDE
                drugs[i].live = true;
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-50;
                drugs[i].boundy = 50;
            }
            else if (rand() % 125 == 0 && drugs[i].x - drugs[i].boundx > drugs[i-1].x + drugs[i-1].boundx)
            {
                //OBSTÁCULO QUE REQUER QUE O JOGADOR ABAIXE
                drugs[i].live = true;
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-95;
                drugs[i].boundy = 50;
            }
        }
    }
}
void UpdateDrug(Drug drugs[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(drugs[i].live)
        {
            drugs[i].x -= drugs[i].speed;
        }
    }
}
void CollideDrug(Drug drugs[], int cSize, Player &player)
{
    for(int i = 0; i < cSize; i++)
    {
        if(drugs[i].live)
        {
            if(drugs[i].x - drugs[i].boundx < player.x + player.boundx &&
                    drugs[i].x + drugs[i].boundx > player.x - player.boundx &&
                    drugs[i].y - drugs[i].boundy < player.y + player.boundy &&
                    drugs[i].y + drugs[i].boundy > player.y - player.boundy)
            {
                player.lives--;
                drugs[i].live = false;
            }
            else if(drugs[i].x < 0)
            {
                drugs[i].live = false;
            }
        }
    }
}
