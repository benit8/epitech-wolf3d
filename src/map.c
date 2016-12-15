/*
** map.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 11:39:29 2016 Benoit Lormeau
** Last update Tue Dec 13 11:39:30 2016 Benoit Lormeau
*/

#include "wolf3d.h"

int	get_map(t_map *map, char *mapPath)
{
  char	*buffer;
  int	i;

  if ((buffer = get_map_buffer(mapPath)) == NULL)
    return (0);
  map->width = get_map_width(buffer);
  map->height = get_map_height(buffer);
  map->map = malloc(sizeof(int *) * map->height);
  i = -1;
  while (++i < map->height)
    map->map[i] = malloc(sizeof(int) * map->width);
  fill_map(buffer, map);
  map->plyrDir = (sfVector2f){0, -1};
  map->plane = (sfVector2f){-1, 0};
  if (map->plyrPos.x == -1)
    return (0);
  free(buffer);
  return (1);
}

char	*get_map_buffer(char *path)
{
  char	*buffer;
  char	buff[3];
  int	bytes;
  int	fd;

  buffer = my_strdup("");
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  while ((bytes = read(fd, buff, 2)) > 0)
    {
      buff[bytes] = '\0';
      buffer = mem_allocat(buffer, buff);
    }
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

void	fill_map(char *buffer, t_map *map)
{
  int	i;
  int	x;
  int	y;

  i = x = y = 0;
  while (buffer[i] != '\0')
    {
      if (buffer[i] == '\n')
	{
	  y++;
	  x = 0;
	}
      else
	{
	  if (buffer[i] == '#')
	    {
	      map->plyrPos = (sfVector2f){y, x};
	      map->map[y][x] = 0;
	    }
	  else
	    map->map[y][x] = buffer[i] - '0';
          x++;
	}
      i++;
    }
}