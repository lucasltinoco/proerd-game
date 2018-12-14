/********************************

* PROERD GAME
* main

* IFSC - Florianópolis
* Programação em Linguagem C

* Lucas  de Lacerda Tinoco
* Igor Willy Gretter Peters

* Data: 14/12/2018
* Revisão: 1v0

*********************************/

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include "globals.h" //variáveis globais
#include "objects.h" //estruturas
#include "player.h" //funções do jogador
#include "drugs&peace.h" //funções dos obstáculos
//#include "clouds.h"

int main(void)
{
    //variáveis primitivas
    bool done = false; //variável do loop principal
    bool redraw = true; //variável
    const int FPS = 60; //definição da velocidade em frames por segundo
    bool isGameOver = false; //define situação do jogo
    int page = 1; //variável que define as páginas do jogo
    int firstoptions = 0; //opções do menu
    bool PlayAgain = false; //opções do final
    int frameCount1 = 0; //primeira contagem de frames
    int frameCount2 = 0; //segunda contagem de frames
    int secondsCount = 0; //contagem em segundos
    int drugCount = 0; //contagem de definição de efeitos das drogas
    int GameTime = 0; //Contador do tempo jogado
    int textspeed = 0; //velocidade do texto de inicialização do jogo
    int altura_sprite = 140, largura_sprite = 108; //largura e altura de cada sprite dentro da folha
    int colunas_folha = 4, coluna_atual = 0; //quantos sprites tem em cada linha da folha, e a atualmente mostrada
    int linha_atual = 0, linhas_folha = 2; //quantos sprites tem em cada coluna da folha, e a atualmente mostrada
    int regiao_x_folha = 0, regiao_y_folha = 0; //posicoes X e Y da folha de sprites que serao mostradas na tela
    int frames_sprite = 3; //quantos frames devem se passar para atualizar para o proximo sprite
    int ground_x1 = 0, ground_x2 = 1000; //posicao X Y da janela em que sera mostrado o sprite

    //variáveis de objeto
    Player player;
    Drug drugs[Freq];
    Peace peace[Freq];
    //Cloud clouds[Freq];

    //variáveis do Allegro
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
    ALLEGRO_BITMAP *playerdown = NULL;
    ALLEGRO_BITMAP *beer = NULL;
    ALLEGRO_BITMAP *tile = NULL;
    ALLEGRO_BITMAP *apple = NULL;
    ALLEGRO_BITMAP *banana = NULL;
    ALLEGRO_BITMAP *pineapple = NULL;
    //ALLEGRO_BITMAP *cloud1 = NULL;
    //ALLEGRO_BITMAP *cloud2 = NULL;
    //ALLEGRO_BITMAP *cloud3 = NULL;
    //ALLEGRO_BITMAP *cloud4 = NULL;
    //ALLEGRO_BITMAP *cloud5 = NULL;
    //ALLEGRO_SAMPLE *musica_proerd=NULL;


    //Funções de inicialização
    if(!al_init()) //inicializa Allegro
        return -1;

    display = al_create_display(WIDTH, HEIGHT); //cria Display

    if(!display) //testa display 
        return -1;
    
    //Carrega addons necessários
    al_init_primitives_addon(); 
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    //al_install_audio();
    //al_init_acodec_addon();
    //al_reserve_samples(1);

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    srand(time(NULL));
    InitPlayer(player); //inicializa jogador
    InitDrugnPeace(drugs, Freq, peace); //inicializa obstáculos
    //InitCloud(clouds, DrugFreq);

    //carregamento de fontes
    font18 = al_load_font("Comic Book.ttf", 18, 0);
    font50 = al_load_font("Comic Book.ttf", 50, 0);
    font60 = al_load_font("Comic Book.ttf", 60, 0);

    //carregamento de imagens
    fundo_proerd = al_load_bitmap("fundo_proerd.png");
    leao_proerd = al_load_bitmap("leao_proerd.png");
    logo_proerd = al_load_bitmap("proerd_logo.png");
    folha_sprite = al_load_bitmap("run2.bmp");
    marijuana = al_load_bitmap("Marijuana.png");
    cocaine = al_load_bitmap("cocaina-png.png");
    playerdown = al_load_bitmap("PlayerDown.bmp");
    beer = al_load_bitmap("beer.png");
    tile = al_load_bitmap("tile.png");
    apple = al_load_bitmap("apple.png");
    banana = al_load_bitmap("banana.png");
    pineapple = al_load_bitmap("pineapple.png");
    //cloud1 = al_load_bitmap("cloud1.png");
    //cloud2 = al_load_bitmap("cloud2.png");
    //cloud3 = al_load_bitmap("cloud3.png");
    //cloud4 = al_load_bitmap("cloud4.png");
    //cloud5 = al_load_bitmap("cloud5.png");

    //musica_proerd = al_load_sample("musica_proerd.ogg");
    //al_play_sample(musica_proerd, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    //REGISTRO DE EVENTOS
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

            //MOVE CHÃO DO JOGO
            ground_x1 = ground_x1 - 8;
            ground_x2 = ground_x2 - 8;
            if(ground_x1 <= -1000)
                ground_x1 = 998;
            if(ground_x2 <= -1000)
                ground_x2 = 998;

            //PULO DO JOGADOR
            if(keys[SPACE])
            {
                if(player.isRising && (player.y < (HEIGHT*5/8)-25) && (player.y > (HEIGHT/2)-25) && player.firstSpace)
                {
                    player.speed = 10;
                    player.isRising = false;
                    player.firstSpace = false;
                }
                else if(!player.isJumping)
                {
                    player.isJumping = true;
                    player.firstSpace = true;
                }
            }

            //AGACHAMENTO OU DESCIDA
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

            //CONFIRMAÇÃO NO MENU INICIAL E FINAL
            if(keys[ENTER])
            {
                if(page == 1)
                {
                    switch(firstoptions)
                    {
                    case 0:
                        page = 2;
                        break;

                    case 1:
                        page = 4;
                        break;

                    case 2:
                        al_destroy_display(display);
                        break;
                    }
                }
                if(page == 3)
                {
                    if(PlayAgain)
                    {
                        redraw = true;
                        page = 2;
                    }
                    else
                        al_destroy_display(display);
                }
            }

            //SE O JOGADOR ATINGE 5 DROGAS, ACABA O JOGO
            if(!isGameOver)
            {
                if(player.drugs > 4)
                    isGameOver = true;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            //MUDANÇA DE OPÇÃO NOS MENUS
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            case ALLEGRO_KEY_UP:
                keys[UP] = true;
                if(page == 1 && firstoptions > 0)
                    firstoptions--;
                break;
            case ALLEGRO_KEY_DOWN:
                keys[DOWN] = true;
                if(page == 1 && firstoptions < 2)
                    firstoptions++;
                break;
            case ALLEGRO_KEY_LEFT:
                keys[LEFT] = true;
                if(page == 3)
                    PlayAgain = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                keys[RIGHT] = true;
                if(page == 3)
                    PlayAgain = false;
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
        //PÁGINA DO MENU DE INICIALIZAÇÃO
        if(redraw && al_is_event_queue_empty(event_queue) && page == 1)
        {
            redraw = false;
            //CARREGA FUNDO E IMAGENS
            al_draw_bitmap(fundo_proerd, 0, 0, 0);
            al_draw_bitmap(leao_proerd, WIDTH/4 - 480/2, 300, 0);
            al_draw_bitmap(logo_proerd, WIDTH/4 - 500/2, HEIGHT/16 - 50, 0);
            //DESENHA OPÇÕES
            switch(firstoptions)
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

        //PÁGINA DO JOGO
        if(redraw && al_is_event_queue_empty(event_queue) && page == 2)
        {
            redraw = false;
            al_clear_to_color(al_map_rgb(91,206,203)); //DESENHA FUNDO
            al_draw_bitmap(tile, ground_x1, HEIGHT*3/4 - 20, 0); //DESENHA CHÃO SE MOVENDO
            al_draw_bitmap(tile, ground_x2, HEIGHT*3/4 - 20, 0);

            if(secondsCount > 12) //INICIA DE FATO O JOGO DEPOIS DE INSTRUÇÕES
            {
                StartDrugnPeace(drugs, Freq, peace); //INICIA OBSTÁCULOS
                UpdateDrugnPeace(drugs, Freq, peace); //ATUALIZA OBSTÁCULOS
                CollideDrugnPeace(drugs, Freq, player, peace, drugCount); //IDENTIFICA COLISÕES
                al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH/4, 25, ALLEGRO_ALIGN_CENTRE, "Tempo: %is", GameTime); //MOSTRA STATUS DO JOGADOR
                al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH/2, 25, ALLEGRO_ALIGN_CENTRE, "Drugs: %is", player.drugs);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 3*WIDTH/4, 25, ALLEGRO_ALIGN_CENTRE, "Fruits: %is", player.peaces);
            }
            if(!isGameOver)
            {
                //StartCloud(clouds, Freq);
                //UpdateCloud(clouds, Freq);
                //DrawCloud(clouds, Freq, cloud1, cloud2, cloud3, cloud4, cloud5);
                //CONTAGEM DE FRAMES E SEGUNDOS
                frameCount1++;
                if(frameCount1 == 60)
                {
                    frameCount1 = 0;
                    secondsCount++;
                    if(secondsCount > 12)
                        GameTime++;
                }
                if(secondsCount < 15) //ESCREVE TEXTO DE INICIALIZAÇÃO
                {
                    textspeed = textspeed + 4;
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - textspeed, HEIGHT/4, 0, "O uso de drogas prejudica o seu futuro e o futuro das pessoas ao seu redor");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - textspeed + 750, HEIGHT/2, 0, "Por isso, fuja das drogas e consuma só o que te faz bem!");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - textspeed*3/4 + 1000, HEIGHT/4, 0, "Opções:");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - textspeed*3/4 + 1000, HEIGHT/4 + 25, 0, "Tecle ESPAÇO para pular");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - textspeed*3/4 + 1000, HEIGHT/4 + 50, 0, "Tecle ESPAÇO 2x para pular mais alto");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - textspeed*3/4 + 1000, HEIGHT/4 + 75, 0, "Tecle SETA PARA BAIXO para descer enquanto no alto");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), WIDTH - textspeed*3/4 + 1000, HEIGHT/4 + 100, 0, "Tecle SETA PARA BAIXO para abaixar-se no chão");
                }
                //CÓDIGO PARA MOVIMENTAR O JOGADOR
                frameCount2++;
                if (frameCount2 >= frames_sprite)
                {
                    frameCount2=0; //reseta cont_frames
                    coluna_atual++; //incrementa a coluna atual, para mostrar o proximo sprite se coluna atual passou da ultima coluna
                    if (coluna_atual >= colunas_folha)
                    {
                        coluna_atual=0;  //volta pra coluna inicial
                        linha_atual = (linha_atual + 1) % linhas_folha;  //incrementa a linha, se passar da ultima, volta pra primeira
                        regiao_y_folha = linha_atual * altura_sprite;  //calcula a posicao Y da folha que sera mostrada
                    }
                    regiao_x_folha = coluna_atual * largura_sprite;  //calcula a regiao X da folha que sera mostrada
                }

                al_convert_mask_to_alpha(folha_sprite,al_map_rgb(255, 0, 255));
                al_convert_mask_to_alpha(playerdown,al_map_rgb(255, 0, 255));
                UpdatePlayer(player); //ATUALIZA JOGADOR CONFORME EFEITOS DAS DROGAS
                if(player.drugEffect > 0)
                {
                    drugCount++; //CONTA O TEMPO PARA PASSAR O EFEITO
                    if(drugCount >= 300)
                    {
                        player.drugEffect = 0;
                        drugCount = 0;
                    }
                }
                DrawPlayer(player); //DESENHA JOGADOR
                if(player.y < (HEIGHT*3/4)-25)
                    al_draw_scaled_bitmap(folha_sprite, 1, 2, 108, 140, player.x - 27, player.y - 35, 54, 70, 0);
                    else if(keys[DOWN] && player.y >= (HEIGHT*3/4)-25)
                        al_draw_scaled_bitmap(playerdown, 0, 0, 108, 140, player.x - 27, player.y - 35, 54, 70, 0);
                        else
                            al_draw_scaled_bitmap(folha_sprite, regiao_x_folha, regiao_y_folha, 108, 140, player.x - 27, player.y - 35, 54, 70, 0);

                if (secondsCount > 12)
                    DrawDrugnPeace(drugs, Freq, peace, player, marijuana, cocaine, beer, apple, banana, pineapple); //DESENHA OBSTÁCULOS
            }
            else
            {
                page = 3;
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
        //PÁGINA FINAL
        if(redraw && al_is_event_queue_empty(event_queue) && page == 3)
        {
            //MOSTRA INFORMAÇÕES DO JOGO
            al_clear_to_color(al_map_rgb(91, 206, 203));
            al_draw_text(font60, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT/4 - 100, ALLEGRO_ALIGN_CENTRE, "GAME OVER!");
            al_draw_textf(font50, al_map_rgb(0, 0, 0), WIDTH/2, HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Frutas Consumidas: %i", player.peaces);
            al_draw_textf(font50, al_map_rgb(0, 0, 0), WIDTH/2, HEIGHT/4 + 100, ALLEGRO_ALIGN_CENTRE, "Tempo: %is", GameTime);
            //APRESENTA OPÇÕES DE JOGAR NOVAMENTE OU SAIR
            if(PlayAgain)
            {
                al_draw_text(font60, al_map_rgb(255, 0, 0), WIDTH/4, 3*HEIGHT/4 - 25, ALLEGRO_ALIGN_CENTRE, "Jogar");
                al_draw_text(font60, al_map_rgb(255, 0, 0), WIDTH/4, 3*HEIGHT/4 + 25, ALLEGRO_ALIGN_CENTRE, "Novamente");
                al_draw_text(font50, al_map_rgb(0, 0, 0), 3*WIDTH/4, 3*HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Sair");
            }
            else
            {
                al_draw_text(font50, al_map_rgb(0, 0, 0), WIDTH/4, 3*HEIGHT/4 - 25, ALLEGRO_ALIGN_CENTRE, "Jogar");
                al_draw_text(font50, al_map_rgb(0, 0, 0), WIDTH/4, 3*HEIGHT/4 + 25, ALLEGRO_ALIGN_CENTRE, "Novamente");
                al_draw_text(font60, al_map_rgb(255, 0, 0), 3*WIDTH/4, 3*HEIGHT/4, ALLEGRO_ALIGN_CENTRE, "Sair");
            }

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0));
        }
    }
    //DESTROI OBJETOS
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_bitmap(logo_proerd);
    al_destroy_bitmap(leao_proerd);
    al_destroy_bitmap(fundo_proerd);
    al_destroy_font(font18);
    al_destroy_font(font50);
    al_destroy_font(font60);
    al_destroy_display(display);

    return 0;
}
