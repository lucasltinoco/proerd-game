/***************************

* PROERD GAME
* reinicialização do jogo

* IFSC - Florianópolis
* Programação em Linguagem C

* Lucas  de Lacerda Tinoco

* Data: 16/12/2018
* Revisão: 1v0

****************************/
//variáveis primitivas
    done = false; //variável do loop principal
    redraw = true; //variável
    isGameOver = false; //define situação do jogo
    firstoptions = 0; //opções do menu
    frameCount1 = 0; //primeira contagem de frames
    frameCount2 = 0; //segunda contagem de frames
    secondsCount = 14; //contagem em segundos
    drugCount = 0; //contagem de definição de efeitos das drogas
    GameTime = -1; //Contador do tempo jogado
    textspeed = 0; //velocidade do texto de inicialização do jogo
    altura_sprite = 140;
    largura_sprite = 108; //largura e altura de cada sprite dentro da folha
    colunas_folha = 4;
    coluna_atual = 0; //quantos sprites tem em cada linha da folha, e a atualmente mostrada
    linha_atual = 0;
    linhas_folha = 2; //quantos sprites tem em cada coluna da folha, e a atualmente mostrada
    regiao_x_folha = 0;
    regiao_y_folha = 0; //posicoes X e Y da folha de sprites que serao mostradas na tela
    frames_sprite = 3; //quantos frames devem se passar para atualizar para o proximo sprite
    ground_x1 = 0;
    ground_x2 = 1000; //posicao X Y da janela em que sera mostrado o sprite

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    srand(time(NULL));
    InitPlayer(player); //inicializa jogador
    InitDrugnPeace(drugs, Freq, peace); //inicializa obstáculos

    //REGISTRO DE EVENTOS
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);
