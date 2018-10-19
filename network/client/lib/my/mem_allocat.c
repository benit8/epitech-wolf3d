/*
** my_strlen.c for wolf3d in /home/benito/delivery/wolf3d/bonus/lib/my
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Fri Dec 16 16:29:37 2016 Benoit Lormeau
** Last update Fri Dec 16 16:29:40 2016 Benoit Lormeau
*/

#include <stdlib.h>

int	my_strlen(char *);
char	*my_strcat(char *, char *);

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