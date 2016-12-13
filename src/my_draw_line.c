/*
** dda.c for bswireframe in /home/benito/delivery/CGP_2016_wireframe_bootstrap
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.net>
** 
** Started on  Tue Nov 15 09:24:02 2016 Benoit Lormeau
** Last update Tue Nov 15 10:04:30 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	my_draw_line(t_framebuffer *fb, sfVector2f from, sfVector2f to, sfColor color)
{
  float	x;
  float	y;
  float	dx;
  float	dy;
  float	ix;
  float	iy;
  int	i;
  int	steps;

  i = -1;
  x = from.x;
  y = from.y;
  dx = to.x - from.x;
  dy = to.y - from.y;
  steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
  ix = dx / (float) steps;
  iy = dy / (float) steps;
  while (++i < steps)
    {
      my_put_pixel(fb, round(x), round(y), color);
      x += ix;
      y += iy;
    }
}