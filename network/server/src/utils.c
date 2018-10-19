/*
** utils.c for sfml in /home/benito/Misc/SFML
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Mon Dec 26 12:54:57 2016 Benoit Lormeau
** Last update Mon Dec 26 12:55:08 2016 Benoit Lormeau
*/

#include "my_sfml.h"

double	radians(double degrees)
{
  return (2 * M_PI * degrees / 360);
}

double	degrees(double radians)
{
  return (360 * radians / (2 * M_PI));
}

float	my_map(float n, float start1, float stop1, float start2, float stop2)
{
  return ((n - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}

float	dist(sfVector2f a, sfVector2f b)
{
  return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}