#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "objects.h"

//GLOBALS==============================
const int WIDTH = 800;
const int HEIGHT = 400;
const int NUM_COMETS = 10;
int N_SPACE = 0;
enum KEYS {UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};

//prototypes
void InitShip(Character &ship);
void DrawShip(Character &ship);

void InitComet(Obstacle comets[], int size);
void DrawComet(Obstacle comets[], int size);
void StartComet(Obstacle comets[], int size);
void UpdateComet(Obstacle comets[], int size);
void CollideComet(Obstacle comets[], int cSize, Character &ship);

int main(void)
{
    //primitive variable
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
    bool isGameOver = false;

    //object variables
    Character character;
    Obstacle comets[NUM_COMETS];

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
    InitShip(character);
    InitComet(comets, NUM_COMETS);

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
                if(character.isJumping && character.isRising && (character.y < (HEIGHT*3/4)-25) && (character.y > (HEIGHT/2)-25))
                {
                    character.speed = 7;
                    character.isRising = false;
                }
                else if(!character.isJumping)
                {
                    character.isJumping = true;
                }
            }


            if(keys[DOWN])
                if(character.isRising)
                {
                    //character.y = (HEIGHT*3/4)-25;
                    character.speed = 0;
                    //character.isJumping = false;
                } else {
                    character.speed = -14;
                }

            if(!isGameOver)
            {
                StartComet(comets, NUM_COMETS);
                UpdateComet(comets, NUM_COMETS);
                CollideComet(comets, NUM_COMETS, character);

                if(character.lives <= 0)
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
                // FireBullet(bullets, NUM_BULLETS, character);
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
                DrawShip(character);
                DrawComet(comets, NUM_COMETS);

                al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has %i lives left. Player has destroyed %i objects", character.lives, character.score);
                al_draw_line(0, HEIGHT*3/4, WIDTH, HEIGHT*3/4, al_map_rgb(0,0,255), 2);
            }
            else
            {
                al_draw_textf(font18, al_map_rgb(0, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i", character.score);
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

void InitShip(Character &character)
{
    character.x = WIDTH/4;
    character.y = (HEIGHT*3/4)-25;
    character.ID = PLAYER;
    character.lives = 3;
    character.speed = 7;
    character.boundx = 25;
    character.boundy = 25;
    character.score = 0;
    character.isJumping = false;
    character.gravity = 0.2;
    character.isRising = false;
}
void DrawShip(Character &character)
{
    //LÓGICA DO PULO COM GRAVIDADE
    if(character.isJumping)
    {
        character.y -= character.speed;
        character.speed -= character.gravity;

        if(character.speed > 0 && (character.y < (HEIGHT*3/4)-25))
        {
            character.isRising = true;
        }
        else
        {
            character.isRising = false;
        }
        //Personagem atingiu o solo
        if(character.y >= (HEIGHT*3/4)-25)
        {
            character.y = (HEIGHT*3/4)-25;
            character.speed = 7;
            character.isJumping = false;
        }
    }
    al_draw_filled_rectangle(character.x-25, character.y-25, character.x + 25, character.y + 25, al_map_rgb(0, 255, 0));
}

void InitComet(Obstacle comets[], int size)
{
    for(int i = 0; i < size; i++)
    {
        comets[i].ID = ENEMY;
        comets[i].live = false;
        comets[i].speed = 5;
        comets[i].boundx = 25;
        comets[i].boundy = 25;
    }
}
void DrawComet(Obstacle comets[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(comets[i].live)
        {
            if(comets[i].big)
            {
                al_draw_filled_rectangle(comets[i].x-25, comets[i].y-75, comets[i].x + 25, comets[i].y + 25, al_map_rgb(255, 0, 0));
            }
            else
            {
                al_draw_filled_rectangle(comets[i].x-25, comets[i].y-25, comets[i].x + 25, comets[i].y + 25, al_map_rgb(255, 0, 0));
            }

        }
    }
}
void StartComet(Obstacle comets[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(!comets[i].live)
        {
            if(rand() % 750 == 0)
            {
                comets[i].live = true;
                comets[i].x = WIDTH;
                comets[i].y = (HEIGHT*3/4)-25;
                if(rand() % 500 == 0)
                    comets[i].big = true;
                break;
            }
        }
    }
}
void UpdateComet(Obstacle comets[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(comets[i].live)
        {
            comets[i].x -= comets[i].speed;
        }
    }
}
void CollideComet(Obstacle comets[], int cSize, Character &ship)
{
    for(int i = 0; i < cSize; i++)
    {
        if(comets[i].live)
        {
            if(comets[i].x - comets[i].boundx < ship.x + ship.boundx &&
                    comets[i].x + comets[i].boundx > ship.x - ship.boundx &&
                    comets[i].y - comets[i].boundy < ship.y + ship.boundy &&
                    comets[i].y + comets[i].boundy > ship.y - ship.boundy)
            {
                ship.lives--;
                comets[i].live = false;
            }
            else if(comets[i].x < 0)
            {
                comets[i].live = false;
            }
        }
    }
}
