/*
** my_strdup.c for wolf3d in /home/benito/delivery/wolf3d/bonus/lib/my
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Fri Dec 16 16:29:37 2016 Benoit Lormeau
** Last update Fri Dec 16 16:29:40 2016 Benoit Lormeau
*/

#include <stdlib.h>

int	my_strlen(char *);
char	*my_strcpy(char *, char *);

char	*my_strdup(char *src)
{
  int	s_len;
  char	*dest;

  s_len = my_strlen(src);
  dest = malloc(sizeof(char) * s_len);
  dest = my_strcpy(dest, src);
  return (dest);
}