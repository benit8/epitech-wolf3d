/*
** my_strlen.c for wolf3d in /home/benito/delivery/wolf3d/bonus/lib/my
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Fri Dec 16 16:29:37 2016 Benoit Lormeau
** Last update Fri Dec 16 16:29:40 2016 Benoit Lormeau
*/

int	my_strlen(char *);

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