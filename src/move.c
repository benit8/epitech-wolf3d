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

void	move_player_forward(t_map *map)
{
  if (map->map[(int) (POS.x + DIR.x * MOVE_SPEED)][(int) POS.y] == 0)
    POS.x += DIR.x * MOVE_SPEED;
  if (map->map[(int) POS.x][(int) (POS.y + DIR.y * MOVE_SPEED)] == 0)
    POS.y += DIR.y * MOVE_SPEED;
}

void	move_player_backward(t_map *map)
{
  if (map->map[(int) (POS.x - DIR.x * MOVE_SPEED)][(int) POS.y] == 0)
    POS.x -= DIR.x * MOVE_SPEED;
  if (map->map[(int) POS.x][(int) (POS.y - DIR.y * MOVE_SPEED)] == 0)
    POS.y -= DIR.y * MOVE_SPEED;
}

void		move_player_right(t_map *map)
{
  sfVector2f	dir;

  dir.x = DIR.x + cos(DIR.x);
  dir.y = DIR.y + 1;
  if (map->map[(int) (POS.x + dir.x * MOVE_SPEED)][(int) POS.y] == 0)
    POS.x += dir.x * MOVE_SPEED;
  if (map->map[(int) POS.x][(int) (POS.y + dir.y * MOVE_SPEED)] == 0)
    POS.y += dir.y * MOVE_SPEED;
}

void		move_player_left(t_map *map)
{
  sfVector2f	dir;

  dir.x = DIR.x - cos(DIR.x);
  dir.y = DIR.y + 1;
  POS.x -= dir.x * MOVE_SPEED;
  POS.y -= dir.y * MOVE_SPEED;
}

void		rotate_player(t_map *map, float speed)
{
  double	oldDirX;
  double	oldPlaneX;

  oldDirX = DIR.x;
  oldPlaneX = map->plane.x;
  DIR.x = DIR.x * cos(speed) - DIR.y * sin(speed);
  DIR.y = oldDirX * sin(speed) + DIR.y * cos(speed);
  map->plane.x = DIR.y * cos(speed) - map->plane.y * sin(speed);
  map->plane.y = oldPlaneX * sin(speed) + map->plane.y * cos(speed);
  // printf("%f, %f\n", DIR.x, DIR.y);
}