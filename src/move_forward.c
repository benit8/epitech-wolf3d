/*
** move_forward.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Mon Dec 12 23:52:05 2016 Benoit Lormeau
** Last update Mon Dec 12 23:52:55 2016 Benoit Lormeau
*/

#include "wolf3d.h"

sfVector2f	move_forward(sfVector2f pos, float direction, float distance)
{
  sfVector2f	res;

  res.x = pos.x + distance * cos(radians(direction));
  res.y = pos.y + distance * sin(radians(direction));
  return (res);
}