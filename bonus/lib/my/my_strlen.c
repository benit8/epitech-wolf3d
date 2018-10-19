/*
** my_strlen.c for wolf3d in /home/benito/delivery/wolf3d/bonus/lib/my
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Fri Dec 16 16:29:37 2016 Benoit Lormeau
** Last update Fri Dec 16 16:29:40 2016 Benoit Lormeau
*/

int	my_strlen(char *s)
{
  return (*s ? 1 + my_strlen(s + 1) : 0);
}