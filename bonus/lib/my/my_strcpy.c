/*
** my_strcpy.c for wolf3d in /home/benito/delivery/wolf3d/bonus/lib/my
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Fri Dec 16 16:29:37 2016 Benoit Lormeau
** Last update Fri Dec 16 16:29:40 2016 Benoit Lormeau
*/

int	my_strlen(char *);

char	*my_strcpy(char *dest, char *src)
{
  int	i;
  int	l;

  i = 0;
  l = my_strlen(src);
  while (i < l)
    {
      dest[i] = src[i];
      i++;
    }
  dest[l] = '\0';
  return (dest);
}