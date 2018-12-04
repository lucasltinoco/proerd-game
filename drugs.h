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
void StartDrug(Drug drugs[], int size, Peace peace[])
{
    for(int i = 0; i < size; i++)
    {
        if(!drugs[i].live && i == size-1)
        {
            switch (rand() % 4)
            {
                case 0: //OBSTÁCULO PEQUENO
                drugs[i].live = true;
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-25;
                drugs[i].boundy = 25;
                break;

                case 1: //OBSTÁCULO FLUTUANTE
                drugs[i].live = true;
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-100;
                drugs[i].boundy = 25;
                break;

                case 2: //OBSTÁCULO GRANDE
                drugs[i].live = true;
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-50;
                drugs[i].boundy = 50;
                break;

                case 3: //OBSTÁCULO QUE REQUER QUE O JOGADOR ABAIXE
                drugs[i].live = true;
                drugs[i].x = WIDTH;
                drugs[i].y = (HEIGHT*3/4)-95;
                drugs[i].boundy = 50;
                break;
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
                player.drugs++;
                drugs[i].live = false;
            }
            else if(drugs[i].x < 0)
            {
                drugs[i].live = false;
            }
        }
    }
}


