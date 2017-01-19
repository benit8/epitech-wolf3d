/*
** raycast.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Thu Dec 15 14:40:08 2016 Benoit Lormeau
** Last update Thu Dec 15 14:40:09 2016 Benoit Lormeau
*/

#include "wolf3d.h"

float		raycast(sfVector2f pos, float dir, int **m, sfVector2i ms)
{
  sfVector2f	ray;
  float		dist;

  ray.x = pos.x;
  ray.y = pos.y;
  dist = 0.0;
  while (ray.x > 0 && ray.y > 0 && ray.x < ms.x && ray.y < ms.y &&
  	 m[(int) ray.y][(int) ray.x] == 0)
    {
      dist += 0.00001;
      ray = move_forward(ray, dir, 0.00001);
    }
  return (dist);
}