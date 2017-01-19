/*
** my_draw_line.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Wed Dec 14 11:15:21 2016 Benoit Lormeau
** Last update Wed Dec 14 11:15:22 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	my_draw_line(t_my_framebuffer *fb,
		     sfVector2i from,
		     sfVector2i to,
		     sfColor color)
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