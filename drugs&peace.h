//INICIALIZA OBSTÁCULOS
void InitDrugnPeace(Drug drugs[], int size, Peace peace[])
{
    for(int i = 0; i < size; i++)
    {
        drugs[i].ID = ENEMY;
        drugs[i].live = false;
        drugs[i].speed = 8;
        drugs[i].boundx = 25;
        drugs[i].boundy = 25;

        peace[i].ID = FRIEND;
        peace[i].live = false;
        peace[i].speed = 8;
        peace[i].boundx = 25;
        peace[i].boundy = 25;
    }
}
//DESENHA IMAGENS DE OBSTÁCULOS E SELECIONA QUAL OBSTÁCULO DE FORMA ALEATORIA
void DrawDrugnPeace(Drug drugs[], int size, Peace peace[], Player &player, ALLEGRO_BITMAP *marijuana, ALLEGRO_BITMAP *cocaine, ALLEGRO_BITMAP *beer, ALLEGRO_BITMAP *apple, ALLEGRO_BITMAP *banana, ALLEGRO_BITMAP *pineapple)
{
    for(int i = 0; i < size; i++)
    {
        if(drugs[i].live)
        {
            if(drugs[i].boundy == 50)
            {
                switch(drugs[i].type)
                {
                    case 0: //MACONHA
                        //al_draw_filled_rectangle(drugs[i].x - 25, drugs[i].y - 50, drugs[i].x + 25, drugs[i].y + 50, al_map_rgb(255, 0, 0));
                        al_draw_bitmap(marijuana, drugs[i].x - 32, drugs[i].y - 64, 0);
                        al_draw_bitmap(marijuana, drugs[i].x - 32, drugs[i].y - 14, 0);
                        drugs[i].boundx = 25;
                    break;

                    case 1: //COCAÍNA
                        //al_draw_filled_rectangle(drugs[i].x - 18, drugs[i].y - 50, drugs[i].x + 18, drugs[i].y + 50, al_map_rgb(255, 0, 0));
                        al_draw_bitmap(cocaine, drugs[i].x - 28, drugs[i].y - 64, 0);
                        al_draw_bitmap(cocaine, drugs[i].x - 28, drugs[i].y + 14, 0);
                        drugs[i].boundx = 25;
                    break;

                    case 2: //BEER
                        //al_draw_filled_rectangle(drugs[i].x - 25, drugs[i].y - 50, drugs[i].x + 25, drugs[i].y + 50, al_map_rgb(255, 0, 0));
                        al_draw_bitmap(beer, drugs[i].x - 30, drugs[i].y - 64, 0);
                        al_draw_bitmap(beer, drugs[i].x - 30, drugs[i].y - 14, 0);
                        drugs[i].boundx = 25;
                    break;
                }
            }
            else
            {
                switch(drugs[i].type)
                {
                    case 0: //MACONHA
                        //al_draw_filled_rectangle(drugs[i].x - 25, drugs[i].y - 25, drugs[i].x + 25, drugs[i].y + 25, al_map_rgb(255, 0, 0));
                        al_draw_bitmap(marijuana, drugs[i].x - 32, drugs[i].y - 39, 0);
                        drugs[i].boundx = 25;
                    break;

                    case 1: //COCAÍNA
                        //al_draw_filled_rectangle(drugs[i].x - 18, drugs[i].y - 25, drugs[i].x + 18, drugs[i].y + 25, al_map_rgb(255, 0, 0));
                        al_draw_bitmap(cocaine, drugs[i].x - 32, drugs[i].y - 14, 0);
                        drugs[i].boundx = 25;
                    break;

                    case 2: //BEER
                        //al_draw_filled_rectangle(drugs[i].x - 18, drugs[i].y - 25, drugs[i].x + 18, drugs[i].y + 25, al_map_rgb(255, 0, 0));
                        al_draw_bitmap(beer, drugs[i].x - 30, drugs[i].y - 34, 0);
                        drugs[i].boundx = 25;
                    break;
                }
            }
        }
        if(peace[i].live){
            //al_draw_filled_rectangle(peace[i].x - 25, peace[i].y - 25, peace[i].x + 25, peace[i].y + 25, al_map_rgb(255, 255, 0));
            switch(peace[i].type)
            {
                case 0: //MAÇÃ
                    al_draw_bitmap(apple, peace[i].x - 32, peace[i].y - 32, 0);
                break;

                case 1: //BANANA
                    al_draw_bitmap(banana, peace[i].x - 32, peace[i].y - 32, 0);
                break;

                case 2: //ABACAXI
                    al_draw_bitmap(pineapple, peace[i].x - 26, peace[i].y - 32, 0);
                break;
            }
        }
  }
}
//INICIA OBSTÁCULOS
void StartDrugnPeace(Drug drugs[], int size, Peace peace[])
{
    for(int i = 0; i < size; i++)
    {
        if(!drugs[i].live && i == size-1)
        {
            switch (rand() % 4)
            {
                case 0: //OBSTÁCULO PEQUENO
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-25;
                drugs[i].live = true;
                drugs[i].boundy = 25;
                break;

                case 1: //OBSTÁCULO FLUTUANTE
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-100;
                drugs[i].live = true;
                drugs[i].boundy = 25;
                break;

                case 2: //OBSTÁCULO GRANDE
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-50;
                drugs[i].live = true;
                drugs[i].boundy = 50;
                break;

                case 3: //OBSTÁCULO QUE REQUER QUE O JOGADOR ABAIXE
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-95;
                drugs[i].live = true;
                drugs[i].boundy = 50;
                break;
            }
            switch(rand() % 3)
            {
                case 0: //MACONHA
                    drugs[i].type = 0;
                break;

                case 1: //COCAÍNA
                    drugs[i].type = 1;
                break;

                case 2: //BEER
                    drugs[i].type = 2;
                break;
            }
        }
        if(!peace[i].live && i == size-1)
        {
            switch (rand() % 10)
            {
                case 0: //OBSTÁCULO PEQUENO
                peace[i].x = WIDTH;
                peace[i].y = (HEIGHT*3/4)-25;
                if (peace[i].x - peace[i].boundx > drugs[i].x + drugs[i].boundx
                 && peace[i].x > (drugs[i].x - drugs[i].boundx - 50)
                 && peace[i].x < (drugs[i].x + drugs[i].boundx + 50))
                    peace[i].live = true;
                break;

                case 1: //OBSTÁCULO FLUTUANTE
                peace[i].x = WIDTH;
                peace[i].y = (HEIGHT*3/4)-125;
                if (peace[i].x - peace[i].boundx > drugs[i].x + drugs[i].boundx
                 && peace[i].x > (drugs[i].x - drugs[i].boundx - 50)
                 && peace[i].x < (drugs[i].x + drugs[i].boundx + 50))
                    peace[i].live = true;
                break;

                case 2: //OBSTÁCULO FLUTUANTE MAIS ALTO
                peace[i].x = WIDTH;
                peace[i].y = (HEIGHT*3/4)-175;
                if (peace[i].x - peace[i].boundx > drugs[i].x + drugs[i].boundx
                 && peace[i].x > (drugs[i].x - drugs[i].boundx - 50)
                 && peace[i].x < (drugs[i].x + drugs[i].boundx + 50))
                    peace[i].live = true;
                break;
            }
            switch(rand() % 3)
            {
                case 0: //MAÇÃ
                    peace[i].type = 0;
                break;

                case 1: //BANANA
                    peace[i].type = 1;
                break;

                case 2: //ABACAXI
                    peace[i].type = 2;
                break;
            }
        }
    }
}
//ATUALIZA A POSIÇÃO DOS OBJETOS
void UpdateDrugnPeace(Drug drugs[], int size, Peace peace[])
{
    for(int i = 0; i < size; i++)
    {
        if(drugs[i].live)
            drugs[i].x -= drugs[i].speed;

        if(peace[i].live)
            peace[i].x -= peace[i].speed;
    }
}
//IDENTIFICA COLISÃO COM O JOGADOR E FIM DE MAPA
void CollideDrugnPeace(Drug drugs[], int cSize, Player &player, Peace peace[], int drugCount)
{
    drugCount++;
    for(int i = 0; i < cSize; i++)
    {
        if(drugs[i].live)
        {
            if(drugs[i].x - drugs[i].boundx < player.x + player.boundx
            && drugs[i].x + drugs[i].boundx > player.x - player.boundx
            && drugs[i].y - drugs[i].boundy < player.y + player.boundy
            && drugs[i].y + drugs[i].boundy > player.y - player.boundy)
            {
                player.drugs++;
                drugs[i].live = false;
                switch(drugs[i].type)
                {
                    case 0:
                        player.drugEffect = 1; // Efeito da Maconha
                        break;
                    case 1:
                        player.drugEffect = 2;
                        break;
                    case 2:
                        player.drugEffect = 3;
                        break;
                };
            }
            else if(drugs[i].x < 0)
                drugs[i].live = false;
        }
        if(peace[i].live)
        {
            if(peace[i].x - peace[i].boundx < player.x + player.boundx
            && peace[i].x + peace[i].boundx > player.x - player.boundx
            && peace[i].y - peace[i].boundy < player.y + player.boundy
            && peace[i].y + peace[i].boundy > player.y - player.boundy)
            {
                player.peaces++;
                peace[i].live = false;
            }
            else if(peace[i].x < 0)
                peace[i].live = false;
        }
    }
}
