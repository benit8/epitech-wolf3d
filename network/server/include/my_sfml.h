/*
** my_sfml.h for sfml in /home/benito/Misc/SFML
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.net>
** 
** Started on  Sun Nov 27 17:41:24 2016 Benoit Lormeau
** Last update Sat Dec 31 20:13:40 2016 Benoit Lormeau
*/

#ifndef	MY_SFML_H_
#define	MY_SFML_H_

# include <stdbool.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <SFML/Network.h>
# include <SFML/System.h>

typedef struct	s_clients{
  sfTcpSocket	*list[8];
  int		count;
}		t_clients;

typedef struct	s_player{
  sfInt8	id;
  sfVector2f	pos;
  sfVector2f	dir;
  int		hp;
}		t_player;

#endif