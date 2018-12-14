//INIICIALIZA JOGADOR
void InitPlayer(Player &player)
{
    player.x = WIDTH/4;
    player.y = (HEIGHT*3/4)-25;
    player.ID = PLAYER;
    player.drugs = 0;
    player.speed = 10;
    player.boundx = 20;
    player.boundy = 25;
    player.peaces = 0;
    player.isJumping = false;
    player.gravity = 0.4;
    player.isRising = false;
    player.firstSpace = false;
    player.drugEffect = 0;
}
//DESENHA JOGADOR
void DrawPlayer(Player &player)
{
    //LÓGICA DO PULO COM GRAVIDADE
    if(player.isJumping)
    {
        player.y -= player.speed;
        player.speed -= player.gravity;

        if(player.speed > 0 && (player.y < (HEIGHT*3/4)-25))
            player.isRising = true;
        else
            player.isRising = false;
    }
    if(keys[DOWN] && player.y >= (HEIGHT*3/4)-25)
    {
        player.y = (HEIGHT*3/4)-20;
        player.boundy = 20;
        //al_draw_filled_rectangle(player.x-20, player.y - 20, player.x + 20, player.y + 20, al_map_rgb(0, 255, 0));
    }
    else if (player.y >= (HEIGHT*3/4)-25)
    {
        player.y = (HEIGHT*3/4)-25;
        player.boundy = 25;
        player.speed = 10;
        player.isJumping = false;
        player.firstSpace = false;
        //al_draw_filled_rectangle(player.x-20, player.y - 25, player.x + 20, player.y + 25, al_map_rgb(0, 255, 0));
    }
    else
    {
        player.boundy = 25;
        //al_draw_filled_rectangle(player.x-20, player.y - 25, player.x + 20, player.y + 25, al_map_rgb(0, 255, 0));
    }
}
//ATUALIZA VELOCIDADE E GRAVIDADE BASEADO NO EFEITO DAS DROGAS
void UpdatePlayer (Player &player)
{
    if(!player.isJumping)
    {
        switch(player.drugEffect)
        {
            case 0:
                player.speed = 10;
                player.gravity = 0.4;
                player.y = (HEIGHT*3/4)-25;
                break;
            case 1:
                player.speed = 0.0001;
                player.gravity = 0.2;
                player.y = (HEIGHT*3/4)-25;
                break;
            case 2:
                player.speed = 1000;
                player.gravity = 0.3;
                player.y = (HEIGHT*3/4)-25;
                break;
            case 3:
                player.speed = 1000;
                player.gravity = 0.6;
                player.y = (HEIGHT*3/4)-25;
                break;
        };
    }
}

