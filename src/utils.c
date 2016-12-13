/*
** utils.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 11:44:43 2016 Benoit Lormeau
** Last update Tue Dec 13 11:44:53 2016 Benoit Lormeau
*/

#include "wolf3d.h"

int	my_strlen(char *s)
{
  return (*s ? 1 + my_strlen(s + 1) : 0);
}

char	*my_strcat(char *dest, char *src)
{
  int	i;
  int	d_len;

  i = 0;
  d_len = my_strlen(dest);
  while (src[i] != '\0')
    {
      dest[d_len + i] = src[i];
      i++;
    }
  dest[d_len + i] = '\0';
  return (dest);
}

char	*mem_allocat(char *a, char *b)
{
  char	*res;
  int	aLen;
  int	bLen;

  aLen = my_strlen(a);
  bLen = my_strlen(b);
  if ((res = malloc(sizeof(char) * (aLen + bLen + 1))) == NULL)
    return (NULL);
  my_strcat(res, a);
  my_strcat(res, b);
  return (res);
}

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

char	*my_strdup(char *src)
{
  int	s_len;
  char	*dest;

  s_len = my_strlen(src);
  dest = malloc(sizeof(char) * s_len);
  dest = my_strcpy(dest, src);
  return (dest);
}