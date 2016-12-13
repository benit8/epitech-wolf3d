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