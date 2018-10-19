/*
** my_swap.c for wolf3d in /home/benito/delivery/wolf3d/bonus/lib/my
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Sat Dec 17 19:37:48 2016 Benoit Lormeau
** Last update Sat Dec 17 19:39:55 2016 Benoit Lormeau
*/

void	int_swap(int *a, int *b)
{
  int	i;

   i = *a;
  *a = *b;
  *b = i;
}

void		double_swap(double *a, double *b)
{
  double	d;

   d = *a;
  *a = *b;
  *b = d;
}
