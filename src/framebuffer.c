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

void	empty_framebuffer(t_framebuffer *fb)
{
  int	i;

  i = -1;
  while (++i < (WIDTH * HEIGHT * 4))
    fb->pixels[i] = 255;
}