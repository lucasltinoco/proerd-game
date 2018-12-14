void InitCloud(Cloud clouds[], int size)
{
    for(int i = 0; i < size; i++)
    {
        clouds[i].speed = 5;
        clouds[i].live = true;
    }
}
void DrawCloud(Cloud clouds[], int size, ALLEGRO_BITMAP *cloud1, ALLEGRO_BITMAP *cloud2, ALLEGRO_BITMAP *cloud3, ALLEGRO_BITMAP *cloud4, ALLEGRO_BITMAP *cloud5)
{
    for(int i = 0; i < size; i++)
    {
        if(clouds[i].live)
        {
            switch(rand() % 5)
            {
            case 0:
                al_draw_filled_rectangle(clouds[i].x - 25, clouds[i].y - 25, clouds[i].x + 25, clouds[i].y + 25, al_map_rgb(255, 255, 0));
                al_draw_bitmap(cloud1, clouds[i].x, clouds[i].y, 0);
                break;
            case 1:
                al_draw_bitmap(cloud2, clouds[i].x, clouds[i].y, 0);
                break;
            case 2:
                al_draw_bitmap(cloud3, clouds[i].x, clouds[i].y, 0);
                break;
            case 3:
                al_draw_bitmap(cloud4, clouds[i].x, clouds[i].y, 0);
                break;
            case 4:
                al_draw_bitmap(cloud5, clouds[i].x, clouds[i].y, 0);
                break;
            };
        }
    }
}

void StartCloud(Cloud clouds[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(!clouds[i].live && i == size - 1)
        {
            switch (rand() % 3)
            {
            case 0:
                clouds[i].x = WIDTH;
                clouds[i].y = (HEIGHT/4)-25;
                break;

            case 1:
                clouds[i].x = WIDTH;
                clouds[i].y = (HEIGHT/4);
                break;

            case 2:
                clouds[i].x = WIDTH;
                clouds[i].y = (HEIGHT/4)+25;
                break;
            }
            switch(rand() % 5)
            {
            case 0:
                clouds[i].type = 0;
                break;
            case 1:
                clouds[i].type = 1;
                break;
            case 2:
                clouds[i].type = 2;
                break;
            case 3:
                clouds[i].type = 3;
                break;
            case 4:
                clouds[i].type = 4;
                break;
            };
        }

    }
}
void UpdateCloud(Cloud clouds[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(clouds[i].live)
            clouds[i].x -= clouds[i].speed;

        if(clouds[i].x < 0)
            clouds[i].live = false;
    }
}

