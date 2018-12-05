void InitDrugnPeace(Drug drugs[], int size, Peace peace[])
{
    for(int i = 0; i < size; i++)
    {
        drugs[i].ID = ENEMY;
        drugs[i].live = false;
        drugs[i].speed = 10;
        drugs[i].boundx = 25;
        drugs[i].boundy = 25;

        peace[i].ID = FRIEND;
        peace[i].live = false;
        peace[i].speed = 10;
        peace[i].boundx = 25;
        peace[i].boundy = 25;
    }
}
void DrawDrugnPeace(Drug drugs[], int size, Peace peace[])
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
        if(peace[i].live)
        {
            al_draw_filled_rectangle(peace[i].x - 25, peace[i].y - 25, peace[i].x + 25, peace[i].y + 25, al_map_rgb(255, 255, 0));
        }
    }
}
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
                //if(peace[i].x + peace[i].boundx < drugs[i].x - drugs[i].boundx)
                //{
                    drugs[i].live = true;
                    drugs[i].boundy = 25;
                //}
                break;

                case 1: //OBSTÁCULO FLUTUANTE
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-100;
                //if(peace[i].x + peace[i].boundx < drugs[i].x - drugs[i].boundx)
                //{
                    drugs[i].live = true;
                    drugs[i].boundy = 25;
                //}
                break;

                case 2: //OBSTÁCULO GRANDE
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-50;
                //if(peace[i].x + peace[i].boundx < drugs[i].x - drugs[i].boundx)
                //{
                    drugs[i].live = true;
                    drugs[i].boundy = 50;
                //}
                break;

                case 3: //OBSTÁCULO QUE REQUER QUE O JOGADOR ABAIXE
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-95;
                //if(peace[i].x + peace[i].boundx < drugs[i].x - drugs[i].boundx)
                //{
                    drugs[i].live = true;
                    drugs[i].boundy = 50;
                //}
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
                if (peace[i].x - peace[i].boundx > drugs[i].x + drugs[i].boundx && peace[i].x > (drugs[i].x - drugs[i].boundx - 50) && peace[i].x < (drugs[i].x + drugs[i].boundx + 50))
                {
                peace[i].live = true;
                }
                break;

                case 1: //OBSTÁCULO FLUTUANTE
                peace[i].x = WIDTH;
                peace[i].y = (HEIGHT*3/4)-125;
                if (peace[i].x - peace[i].boundx > drugs[i].x + drugs[i].boundx && peace[i].x > (drugs[i].x - drugs[i].boundx - 50) && peace[i].x < (drugs[i].x + drugs[i].boundx + 50))
                {
                peace[i].live = true;
                }
                break;

                case 2: //OBSTÁCULO FLUTUANTE MAIS ALTO
                peace[i].x = WIDTH;
                peace[i].y = (HEIGHT*3/4)-175;
                if (peace[i].x - peace[i].boundx > drugs[i].x + drugs[i].boundx && peace[i].x > (drugs[i].x - drugs[i].boundx - 50) && peace[i].x < (drugs[i].x + drugs[i].boundx + 50))
                {
                peace[i].live = true;
                }
                break;
            }
        }
    }
}
void UpdateDrugnPeace(Drug drugs[], int size, Peace peace[])
{
    for(int i = 0; i < size; i++)
    {
        if(drugs[i].live)
        {
            drugs[i].x -= drugs[i].speed;
        }
        if(peace[i].live)
        {
            peace[i].x -= peace[i].speed;
        }
    }
}
void CollideDrugnPeace(Drug drugs[], int cSize, Player &player, Peace peace[])
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
                player.drugs++;
                drugs[i].live = false;
            }
            else if(drugs[i].x < 0)
            {
                drugs[i].live = false;
            }
        }
        if(peace[i].live)
        {
            if(peace[i].x - peace[i].boundx < player.x + player.boundx &&
                    peace[i].x + peace[i].boundx > player.x - player.boundx &&
                    peace[i].y - peace[i].boundy < player.y + player.boundy &&
                    peace[i].y + peace[i].boundy > player.y - player.boundy)
            {
                player.peaces++;
                peace[i].live = false;
            }
            else if(peace[i].x < 0)
            {
                peace[i].live = false;
            }
        }
    }
}


