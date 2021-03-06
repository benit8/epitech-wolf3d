/*
** framebuffer.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 11:37:41 2016 Benoit Lormeau
** Last update Tue Dec 13 11:37:42 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	empty_framebuffer(t_my_framebuffer *fb)
{
  for (int i = 0; i < (WIDTH * HEIGHT * 4); ++i)
    fb->pixels[i] = 255;
}

void	redraw_ui(t_my_framebuffer *fb)
{
  int	i;

  i = WIDTH * (HEIGHT - (UI_H + 1)) * 4;
  while (i < WIDTH * HEIGHT * 4)
    {
      fb->pixels[i + 0] = 44;
      fb->pixels[i + 1] = 42;
      fb->pixels[i + 2] = 40;
      fb->pixels[i + 3] = 255;
      i += 4;
    }
}