/*
** color.c for sfml in /home/benito/Misc/SFML
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Mon Dec 26 17:03:48 2016 Benoit Lormeau
** Last update Mon Dec 26 17:03:54 2016 Benoit Lormeau
*/

#include "my_sfml.h"

//				[0  -  1]  [0  -  1]  [0 - 255]
sfColor		sfColor_fromHSB(float hue, float sat, float val)
{
  int		tint1, tint2, tint3;
  int		sector;

  hue *= 6;
  if (sat == 0)
    return ((sfColor){val, val, val, 255});
  else
    {
      sector = floor(hue);
      tint1 = val * (1 - sat);
      tint2 = val * (1 - sat * (hue - sector));
      tint3 = val * (1 - sat * (1 + sector - hue));
      if (sector == 1)
	return ((sfColor){tint2, val, tint1, 255});
      else if (sector == 2)
	return ((sfColor){tint1, val, tint3, 255});
      else if (sector == 3)
	return ((sfColor){tint1, tint2, val, 255});
      else if (sector == 4)
	return ((sfColor){tint3, tint1, val, 255});
      else if (sector == 5)
	return ((sfColor){val, tint1, tint2, 255});
      else
	return ((sfColor){val, tint3, tint1, 255});
    }
}