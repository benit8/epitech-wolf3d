/*
** map.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 11:39:29 2016 Benoit Lormeau
** Last update Tue Dec 13 11:39:30 2016 Benoit Lormeau
*/

#include "my.h"
#include "wolf3d.h"

char	*get_map_buffer(char *);
void	fill_map(char *, t_map *, t_plyr *);
int	get_map_height(char *);
int	get_map_width(char *);

int	get_map(t_map *map, t_plyr *player)
{
  char	*buffer;

  if ((buffer = get_map_buffer(map->path)) == NULL)
    return (0);

  map->width = get_map_width(buffer);
  map->height = get_map_height(buffer);
  map->map = malloc(sizeof(char *) * map->height);

  for (int i = 0; i < map->height; ++i)
    map->map[i] = malloc(sizeof(char) * map->width);

  player->pos = (sfVector2f){-1, -1};
  fill_map(buffer, map, player);
  player->weapon = 0;
  player->isShooting = 0;

  if (player->pos.x == -1) return (0);
  free(buffer);
  return (1);
}

void	fill_map(char *buffer, t_map *map, t_plyr *player)
{
  int	i;
  int	x;
  int	y;

  i = x = y = 0;
  while (buffer[i] != '\0')
    {
      if (buffer[i] == '\n'){
	y++;
	x = 0; }
      else
	{
	  if (in_array(buffer[i], "^<>_")){
	    switch (buffer[i]){
	      case '^':
		player->dir   = (sfVector2f){-1, 0};
		player->plane = (sfVector2f){0, 1};
	      break;
	      case '<':
		player->dir   = (sfVector2f){0, -1};
		player->plane = (sfVector2f){-1, 0};
	      break;
	      case '>':
		player->dir   = (sfVector2f){0, 1};
		player->plane = (sfVector2f){1, 0};
	      break;
	      case '_':
		player->dir   = (sfVector2f){1, 0};
		player->plane = (sfVector2f){0, -1};
	      break;
	    }

	    player->pos = (sfVector2f){y + 0.5, x + 0.5};
	    map->map[y][x] = ' ';
	  }
	  else
	    map->map[y][x] = buffer[i];
	  x++;
	}
      i++;
    }
}

char		*get_map_buffer(char *path)
{
  struct stat	infos;
  char		*buffer;
  int		bytes;
  int		fd;

  stat(path, &infos);
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  if ((buffer = malloc(sizeof(char) * (infos.st_size + 1))) == NULL)
    return (NULL);
  bytes = read(fd, buffer, infos.st_size);
  buffer[bytes] = '\0';

  return (buffer);
}

int	get_map_height(char *buffer)
{
  int	i;
  int	c;

  i = c = 0;
  while (buffer[i] != '\0')
    {
      if (buffer[i] == '\n')
        c++;
      i++;
    }
  return (++c);
}

int	get_map_width(char *buffer)
{
  int	i;
  int	l;
  int	w;

  i = l = w = 0;
  while (buffer[i] != '\0')
    {
      if (buffer[i] == '\n')
	{
	  w = w > l ? w : l;
	  l = 0;
	}
      else
        l++;
      i++;
    }
  return (w);
}