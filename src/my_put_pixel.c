/*
** my_put_pixel.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Wed Dec 14 11:15:09 2016 Benoit Lormeau
** Last update Wed Dec 14 11:15:11 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	my_put_pixel(t_my_framebuffer *fb, int x, int y, sfColor color)
{
  int		idx;

  idx = (fb->width * y + x) * 4;
  if (idx >= 0 && idx < (fb->width * fb->height * 4 - 4) &&
      ((y >= 0 && y < fb->height) && (x >= 0 && x < fb->width)))
    {
      fb->pixels[idx + 0] = color.r;
      fb->pixels[idx + 1] = color.g;
      fb->pixels[idx + 2] = color.b;
      fb->pixels[idx + 3] = color.a;
    }
}