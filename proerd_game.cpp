#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "globals.h"
#include "objects.h"
#include "player.h"
#include "drugs&peace.h"

int main(void)
{
    //primitive variable
    bool done = false;
    bool redraw = true;
    const int FPS = 60;
    bool isGameOver = false;
    int page = 1;
    int options = 0;
    int frameCount1 = 0;
    int frameCount2 = 0;
    int secondsCount = 0;
    int textspeed = 0;
    //largura e altura de cada sprite dentro da folha
    int altura_sprite=140, largura_sprite=108;
    //quantos sprites tem em cada linha da folha, e a atualmente mostrada
    int colunas_folha=4, coluna_atual=0;
        //quantos sprites tem em cada coluna da folha, e a atualmente mostrada
    int linha_atual=0, linhas_folha=2;
    //posicoes X e Y da folha de sprites que serao mostradas na tela
    int regiao_x_folha=0, regiao_y_folha=0;
    //quantos frames devem se passar para atualizar para o proximo sprite
    int frames_sprite=6;
    //posicao X Y da janela em que sera mostrado o sprite

    //object variables
    Player player;
    Drug drugs[DrugFreq];
    Peace peace[PeaceFreq];

    //Allegro variables
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font18 = NULL;
    ALLEGRO_FONT *font50 = NULL;
    ALLEGRO_FONT *font60 = NULL;
    ALLEGRO_BITMAP *logo_proerd = NULL;
    ALLEGRO_BITMAP *leao_proerd = NULL;
    ALLEGRO_BITMAP *fundo_proerd = NULL;
    ALLEGRO_BITMAP *folha_sprite = NULL;
    ALLEGRO_BITMAP *marijuana = NULL;
    ALLEGRO_BITMAP *cocaine = NULL;

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
    al_init_image_addon();

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    srand(time(NULL));
    InitPlayer(player);
    InitDrugnPeace(drugs, DrugFreq, peace);


    font18 = al_load_font("Comic Book.ttf", 18, 0);
    font50 = al_load_font("Comic Book.ttf", 50, 0);
    font60 = al_load_font("Comic Book.ttf", 60, 0);

    fundo_proerd = al_load_bitmap("fundo_proerd.png");
    leao_proerd = al_load_bitmap("leao_proerd.png");
    logo_proerd = al_load_bitmap("proerd_logo.png");
    folha_sprite = al_load_bitmap("run2.bmp");
    marijuana = al_load_bitmap("Marijuana.png");
    cocaine = al_load_bitmap("Cocaine.png");

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
            {
                if(player.isRising)
                {
                    player.speed = 0;
                }
                else
                {
                    player.speed = -14;
                }
            }

            if(keys[ENTER])
                if(page == 1)
                {
                    switch(options)
                    {
                        case 0:
                            page = 2;
                        break;

                        case 1:
                            page = 3;
                        break;

                        case 2:
                            al_destroy_display(display);
                        break;
                    }
                }

            if(!isGameOver)
            {
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
                if(page == 1 && options > 0)
                    options--;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                if(page == 1 && options < 2)
                    options++;
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
            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = true;
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
            case ALLEGRO_KEY_ENTER:
                keys[ENTER] = false;
                break;
            }
        }
        if(redraw && al_is_event_queue_empty(event_queue) && page == 1) //MENU
        {
            redraw = false;

            al_draw_bitmap(fundo_proerd, 0, 0, 0);
            al_draw_bitmap(leao_proerd, WIDTH/4 - 480/2, 300, 0);
            al_draw_bitmap(logo_proerd, WIDTH/4 - 500/2, HEIGHT/16 - 50, 0);
            switch(options)
            {
                case 0:
                al_draw_text(font60, al_map_rgb(255, 0, 0), 3*WIDTH/4, HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Jogar");
                al_draw_text(font50, al_map_rgb(0, 0, 0), 3*WIDTH/4, 2*HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Créditos");
                al_draw_text(font50, al_map_rgb(0, 0, 0), 3*WIDTH/4, 3*HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Sair");
                break;

                case 1:
                al_draw_text(font50, al_map_rgb(0, 0, 0), 3*WIDTH/4, HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Jogar");
                al_draw_text(font60, al_map_rgb(255, 0, 0), 3*WIDTH/4, 2*HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Créditos");
                al_draw_text(font50, al_map_rgb(0, 0, 0), 3*WIDTH/4, 3*HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Sair");
                break;

                case 2:
                al_draw_text(font50, al_map_rgb(0, 0, 0), 3*WIDTH/4, HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Jogar");
                al_draw_text(font50, al_map_rgb(0, 0, 0), 3*WIDTH/4, 2*HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Créditos");
                al_draw_text(font60, al_map_rgb(255, 0, 0), 3*WIDTH/4, 3*HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Sair");
                break;
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }


        if(redraw && al_is_event_queue_empty(event_queue) && page == 2)
        {
            redraw = false;
            if(secondsCount > 20)
            {
                StartDrugnPeace(drugs, DrugFreq, peace);
                UpdateDrugnPeace(drugs, DrugFreq, peace);
                CollideDrugnPeace(drugs, DrugFreq, player, peace);
            }

            if(!isGameOver)
            {
                frameCount1++;
                if(frameCount1 == 60)
                {
                    frameCount1 = 0;
                    secondsCount++;
                }
                al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 25, 0, "Tempo decorrido: %is", secondsCount);
                if(secondsCount < 22)
                {
                    textspeed = textspeed + 4;
                    al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH - textspeed, HEIGHT/4, 0, "O uso de drogas prejudica o seu futuro e o futuro das pessoas ao seu redor");
                    al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH - textspeed + 1000, HEIGHT/2, 0, "Por isso, fuja das drogas e consuma só o que te faz bem!");
                    al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH - textspeed/2 + 1000, HEIGHT/4, 0, "Opções:");
                    al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH - textspeed/2 + 1000, HEIGHT/4 + 25, 0, "Tecle ESPAÇO para pular");
                    al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH - textspeed/2 + 1000, HEIGHT/4 + 50, 0, "Tecle ESPAÇO 2x para pular mais alto");
                    al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH - textspeed/2 + 1000, HEIGHT/4 + 75, 0, "Tecle SETA PARA BAIXO para descer enquanto no alto");
                    al_draw_textf(font18, al_map_rgb(255, 0, 255), WIDTH - textspeed/2 + 1000, HEIGHT/4 + 100, 0, "Tecle SETA PARA BAIXO para abaixar-se no chão");
                }
                frameCount2++;
                if (frameCount2 >= frames_sprite)
                {
                    //reseta cont_frames
                    frameCount2=0;
                    //incrementa a coluna atual, para mostrar o proximo sprite
                    coluna_atual++;
                    //se coluna atual passou da ultima coluna
                    if (coluna_atual >= colunas_folha)
                    {
                        //volta pra coluna inicial
                        coluna_atual=0;
                        //incrementa a linha, se passar da ultima, volta pra primeira
                        linha_atual = (linha_atual + 1) % linhas_folha;
                        //calcula a posicao Y da folha que sera mostrada
                        regiao_y_folha = linha_atual * altura_sprite;
                    }
                    //calcula a regiao X da folha que sera mostrada
                    regiao_x_folha = coluna_atual * largura_sprite;
                }
                al_convert_mask_to_alpha(folha_sprite,al_map_rgb(255, 0, 255));
                DrawPlayer(player);
                if(player.isJumping)
                    al_draw_scaled_bitmap(folha_sprite, 1, 2, 108, 140, player.x - 27, player.y - 35, 54, 70, 0);
                    else
                        al_draw_scaled_bitmap(folha_sprite, regiao_x_folha, regiao_y_folha, 108, 140, player.x - 27, player.y - 35, 54, 70, 0);

                if (secondsCount > 20)
                    DrawDrugnPeace(drugs, DrugFreq, peace, player, marijuana, cocaine);

                al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "Player has used %i drugs. Player has collected %i good objects", player.drugs, player.peaces);
                al_draw_line(0, HEIGHT*3/4, WIDTH, HEIGHT*3/4, al_map_rgb(0,0,255), 2);
            }
            else
                al_draw_textf(font18, al_map_rgb(0, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Game Over. Final Score: %i", player.peaces);

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(logo_proerd);
    al_destroy_bitmap(leao_proerd);
    al_destroy_bitmap(fundo_proerd);
    al_destroy_font(font18);
    al_destroy_font(font50);
    al_destroy_font(font60);
    al_destroy_display(display);						//destroy our display object

    return 0;
}
