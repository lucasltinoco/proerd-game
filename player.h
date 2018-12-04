void InitPlayer(Player &player)
{
    player.x = WIDTH/4;
    player.y = (HEIGHT*3/4)-25;
    player.ID = PLAYER;
    player.drugs = 0;
    player.speed = 7;
    player.boundx = 25;
    player.boundy = 25;
    player.peaces = 0;
    player.isJumping = false;
    player.gravity = 0.2;
    player.isRising = false;
    player.firstSpace = false;
}
void DrawPlayer(Player &player)
{
    //LÓGICA DO PULO COM GRAVIDADE
    if(player.isJumping)
    {
        player.y -= player.speed;
        player.speed -= player.gravity;

        if(player.speed > 0 && (player.y < (HEIGHT*3/4)-25))
        {
            player.isRising = true;
        }
        else
        {
            player.isRising = false;
        }
    }
    if(keys[DOWN] && player.y >= (HEIGHT*3/4)-25)
    {
        player.y = (HEIGHT*3/4)-20;
        player.boundy = 20;
        al_draw_filled_rectangle(player.x-25, player.y - 20, player.x + 25, player.y + 20, al_map_rgb(0, 255, 0));
    }
    else if (player.y >= (HEIGHT*3/4)-25)
    {
        player.y = (HEIGHT*3/4)-25;
        player.boundy = 25;
        player.speed = 7;
        player.isJumping = false;
        player.firstSpace = false;
        al_draw_filled_rectangle(player.x-25, player.y - 25, player.x + 25, player.y + 25, al_map_rgb(0, 255, 0));
    }
    else
    {
        player.boundy = 25;
        al_draw_filled_rectangle(player.x-25, player.y - 25, player.x + 25, player.y + 25, al_map_rgb(0, 255, 0));
    }
}
