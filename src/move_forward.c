/*
** move_forward.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Wed Dec 14 10:03:29 2016 Benoit Lormeau
** Last update Wed Dec 14 10:03:31 2016 Benoit Lormeau
*/

#include "wolf3d.h"

double	radians(double degrees)
{
  return (2 * M_PI * degrees / 360);
}

sfVector2f	move_forward(sfVector2f pos, float direction, float distance)
{
  sfVector2f	res;

  res.x = pos.x + distance * cos(radians(direction));
  res.y = pos.y + distance * sin(radians(direction));
  return (res);
}