/*
** player.c for wolf3d in /home/benito/Misc/wolf3d-network/client
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Jan 10 14:45:06 2017 Benoit Lormeau
** Last update Tue Jan 10 14:45:08 2017 Benoit Lormeau
*/

#include "wolf3d.h"

void	you_died(t_vars *vars)
{
  for (int y = (int)HEIGHT * 0.4; y < (int)HEIGHT * 0.6; ++y){
    my_draw_line(vars->framebuffer, (sfVector2i){0, y}, (sfVector2i){WIDTH, y}, sfColor_fromRGBA(0, 0, 0, 180));
  }

  sfTexture_updateFromPixels(vars->texture, vars->framebuffer->pixels, WIDTH, HEIGHT, 0, 0);
  sfSprite_setTexture(vars->sprite, vars->texture, sfTrue);
  sfRenderWindow_drawSprite(vars->rWindow, vars->sprite, NULL);
  sfRenderWindow_drawText(vars->rWindow, vars->textDead, NULL);
}

void	respawn(t_plyr *player, t_map *map, t_net *net)
{
  int	i = randint(map->spawnCount);
  player->hp = 100;

  player->pos.x = map->spawns[i].pos.x;
  player->pos.y = map->spawns[i].pos.y;
  player->dir.x = map->spawns[i].dir.x;
  player->dir.y = map->spawns[i].dir.y;
  player->plane.x = map->spawns[i].pln.x;
  player->plane.y = map->spawns[i].pln.y;

  sendRes(net);
  sendPos(player, net);
  sendDir(player, net);
}