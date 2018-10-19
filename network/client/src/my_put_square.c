/*
** my_put_square.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.net>
** 
** Started on  Wed Dec 14 11:08:22 2016 Benoit Lormeau
** Last update Wed Dec 14 11:08:23 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	my_put_square(t_my_framebuffer *fb, sfIntRect sqr, sfColor color)
{
  int	x;
  int	y;

  y = -1;
  while (++y < sqr.height)
    {
      x = -1;
      while (++x < sqr.width)
        my_put_pixel(fb, round(sqr.left + x), round(sqr.top + y), color);
    }
}