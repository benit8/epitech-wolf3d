/*
** move.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Mon Dec 12 23:52:05 2016 Benoit Lormeau
** Last update Mon Dec 12 23:52:55 2016 Benoit Lormeau
*/

#include "wolf3d.h"

size_t inc = 0;
unsigned short delay = 3;

void	move_player_forward(t_map *map, t_plyr *player, float sec, t_net *net)
{
  float	move_speed;

  move_speed = sec * MOVE_SPEED;
  if (map->map[(int) (POS.x + DIR.x * move_speed)][(int) POS.y] == ' ')
    POS.x += DIR.x * move_speed;
  if (map->map[(int) POS.x][(int) (POS.y + DIR.y * move_speed)] == ' ')
    POS.y += DIR.y * move_speed;

  if (++inc % delay == 0)
    sendPos(player, net);
}

void	move_player_backward(t_map *map, t_plyr *player, float sec, t_net *net)
{
  float	move_speed;

  move_speed = sec * MOVE_SPEED;
  if (map->map[(int) (POS.x - DIR.x * move_speed)][(int) POS.y] == ' ')
    POS.x -= DIR.x * move_speed;
  if (map->map[(int) POS.x][(int) (POS.y - DIR.y * move_speed)] == ' ')
    POS.y -= DIR.y * move_speed;

  if (++inc % delay == 0)
    sendPos(player, net);
}

void		rotate_player(t_plyr *player, float speed, t_net *net)
{
  double	oldDirX;
  double	oldPlaneX;

  oldDirX = DIR.x;
  oldPlaneX = PLN.x;
  DIR.x = DIR.x * cos(speed) - DIR.y * sin(speed);
  DIR.y = oldDirX * sin(speed) + DIR.y * cos(speed);
  PLN.x = DIR.y * cos(speed) - PLN.y * sin(speed);
  PLN.y = oldPlaneX * sin(speed) + PLN.y * cos(speed);

  if (++inc % delay == 0)
    sendDir(player, net);
}