void InitPeace(Peace peace[], int size)
{
    for(int i = 0; i < size; i++)
    {
        peace[i].ID = ENEMY;
        peace[i].live = false;
        peace[i].speed = 5;
        peace[i].boundx = 25;
        peace[i].boundy = 25;
    }
}
void DrawPeace(Peace peace[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(peace[i].live)
        {
            al_draw_filled_rectangle(peace[i].x - 25, peace[i].y - 25, peace[i].x + 25, peace[i].y + 25, al_map_rgb(255, 255, 0));
        }
    }
}
void StartPeace(Peace peace[], int size, Drug drugs[])
{
    for(int i = 0; i < size; i++)
    {
        if(!peace[i].live)
        {
            if(rand() % 1250 == 0 && peace[i].x - peace[i].boundx > peace[i-1].x + peace[i-1].boundx)
            {
                //OBSTÁCULO PEQUENO
                peace[i].live = true;
                peace[i].x = WIDTH;
                peace[i].y = (HEIGHT*3/4)-25;
            }
            else if (rand() % 1250 == 0 && peace[i].x - peace[i].boundx > peace[i-1].x + peace[i-1].boundx && peace[i].x - peace[i].boundx> drugs[i-1].x + drugs[i-1].boundx)
            {
                //OBSTÁCULO FLUTUANTE
                peace[i].live = true;
                peace[i].x = WIDTH;
                peace[i].y = (HEIGHT*3/4)-125;
            }
        }
    }
}
void UpdatePeace(Peace peace[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(peace[i].live)
        {
            peace[i].x -= peace[i].speed;
        }
    }
}
void CollidePeace(Peace peace[], int cSize, Player &player)
{
    for(int i = 0; i < cSize; i++)
    {
        if(peace[i].live)
        {
            if(peace[i].x - peace[i].boundx < player.x + player.boundx &&
                    peace[i].x + peace[i].boundx > player.x - player.boundx &&
                    peace[i].y - peace[i].boundy < player.y + player.boundy &&
                    peace[i].y + peace[i].boundy > player.y - player.boundy)
            {
                player.score++;
                peace[i].live = false;
            }
            else if(peace[i].x < 0)
            {
                peace[i].live = false;
            }
        }
    }
}


