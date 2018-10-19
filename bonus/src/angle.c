/*
** angle.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 11:23:20 2016 Benoit Lormeau
** Last update Tue Dec 13 11:23:24 2016 Benoit Lormeau
*/

#include "wolf3d.h"

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


sfVector2f	vectCopy(sfVector2f v)
{
  sfVector2f	r;

  r.x = v.x;
  r.y = v.y;

  return (r);
}

sfVector2f	vectAdd(sfVector2f a, sfVector2f b)
{
  sfVector2f	r;

  r.x = a.x + b.x;
  r.y = a.y + b.y;

  return (r);
}

sfVector2f	vectSub(sfVector2f a, sfVector2f b)
{
  sfVector2f	r;

  r.x = a.x - b.x;
  r.y = a.y - b.y;

  return (r);
}

sfVector2f	vectMul(sfVector2f v, float d)
{
  v.x *= d;
  v.y *= d;

  return (v);
}

sfVector2f	vectDiv(sfVector2f v, float d)
{
  v.x /= d;
  v.y /= d;

  return (v);
}

float	vectDistSq(sfVector2f a, sfVector2f b)
{
  return (pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float	vectMag(sfVector2f v)
{
  return (sqrt(v.x * v.x + v.y * v.y));
}

sfVector2f	vectSetMag(sfVector2f v, float m)
{
  return (vectMul(vectNormalize(v), m));
}

sfVector2f	vectNormalize(sfVector2f v)
{
  return vectMag(v) == 0 ? v : vectDiv(v, vectMag(v));
}