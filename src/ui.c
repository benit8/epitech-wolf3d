/*
** mini_map.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Wed Dec 14 11:08:22 2016 Benoit Lormeau
** Last update Wed Dec 14 11:08:23 2016 Benoit Lormeau
*/

#include "wolf3d.h"

sfVector2i	mini_map(t_vars *vars, t_map *map)
{
  int		y;
  int		x;
  int		scl;
  int		off;
  sfIntRect	sqr;

  scl = UI_H / map->height;
  off = (UI_H - map->height * scl) / 2;
  y = -1;
  while (++y < map->height)
    {
      x = -1;
      while (++x < map->width)
	{
	  sqr.width = sqr.height = scl;
	  sqr.left = WIDTH - UI_H + (x * scl) + off;
	  sqr.top  = HEIGHT - UI_H + (y * scl) + off;
	  if (map->map[y][x] != 0)
	    my_put_square(vars->framebuffer, sqr, sfWhite);
	  else
	    my_put_square(vars->framebuffer, sqr, sfBlack);
	}
    }
  return ((sfVector2i){WIDTH - UI_H + (map->plyrPos.y * scl) + off,
		       HEIGHT - UI_H + (map->plyrPos.x * scl) + off});
}

void	mini_map_player(t_vars *vars, t_map *map, sfVector2i pos)
{
  float	angle;

  angle = degrees(acos(map->plyrDir.x)) + 180;
  if (degrees(asin(map->plyrDir.y)) > 0)
    angle *= -1;
  vars->mapPlyrVertices = sfVertexArray_create();
  vars->mapPlyrStates->transform = sfTransform_Identity;
  sfVertexArray_setPrimitiveType(vars->mapPlyrVertices, sfTriangles);
  sfVertexArray_append(vars->mapPlyrVertices, (sfVertex){(sfVector2f){pos.x,     pos.y - 10}, sfRed, (sfVector2f){0, 0}});
  sfVertexArray_append(vars->mapPlyrVertices, (sfVertex){(sfVector2f){pos.x + 5, pos.y + 6 }, sfRed, (sfVector2f){0, 0}});
  sfVertexArray_append(vars->mapPlyrVertices, (sfVertex){(sfVector2f){pos.x - 5, pos.y + 6 }, sfRed, (sfVector2f){0, 0}});
  sfTransform_rotateWithCenter(&vars->mapPlyrStates->transform, angle, pos.x, pos.y);
}

void	cross(t_my_framebuffer *fb)
{
  my_draw_line(fb, (sfVector2i){WIDTH / 2, ((HEIGHT - UI_H) / 2) - 10},
		   (sfVector2i){WIDTH / 2, ((HEIGHT - UI_H) / 2) + 10}, sfRed);
  my_draw_line(fb, (sfVector2i){WIDTH / 2 - 10, ((HEIGHT - UI_H) / 2)},
		   (sfVector2i){WIDTH / 2 + 10, ((HEIGHT - UI_H) / 2)}, sfRed);
}