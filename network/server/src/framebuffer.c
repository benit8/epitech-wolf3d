/*
** framebuffer.c for sfml in /home/benito/Misc/SFML
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Mon Dec 26 15:35:38 2016 Benoit Lormeau
** Last update Mon Dec 26 15:35:48 2016 Benoit Lormeau
*/

#include "my_sfml.h"

void	empty_framebuffer(t_my_framebuffer *fb)
{
  int	i;

  i = 0;
  while (i < (WIDTH * HEIGHT * 4))
    fb->pixels[i++] = 255;
}

void	my_put_pixel(t_my_framebuffer *fb, int x, int y, sfColor color)
{
  int	idx;

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

void	my_draw_line(t_my_framebuffer *fb,
			   sfVector2i  from,
			   sfVector2i  to,
			      sfColor  color)
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