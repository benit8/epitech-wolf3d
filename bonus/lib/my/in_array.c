/*
** in_array.c for wolf3d in /home/benito/delivery/wolf3d/bonus/lib/my
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Fri Dec 16 16:34:04 2016 Benoit Lormeau
** Last update Fri Dec 16 16:34:11 2016 Benoit Lormeau
*/

int	in_array(char needle, char *haystack)
{
  int	i;

  i = 0;
  while (haystack[i])
    {
      if (haystack[i] == needle)
	return (1);
      i++;
    }
  return (0);
}