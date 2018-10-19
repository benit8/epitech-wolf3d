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
bool	fill_map(char *, t_map *);
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

  if (!fill_map(buffer, map)) return (0);
  player->hp = 100;
  player->weapon = 1;
  player->isShooting = 0;

  free(buffer);
  return (1);
}

bool	fill_map(char *buffer, t_map *map)
{
  int	x, y, i, j;

  map->spawnCount = 0;
  for (i = x = y = 0; buffer[i] != '\0'; ++i){
    if (buffer[i] == '\n'){
      y++;
      x = 0; }
    else {
      if (in_array(buffer[i], "^<>_"))
        map->spawnCount++;
      else
        map->map[y][x] = buffer[i];
      x++;
    }
  }

  if ((map->spawns = malloc(sizeof(t_spwn) * map->spawnCount)) == NULL)
    return (false);

  for (i = j = x = y = 0; buffer[i] != '\0'; ++i){
    if (buffer[i] == '\n'){
      y++;
      x = 0; }
    else {
      if (in_array(buffer[i], "^<>_")){
        map->map[y][x] = ' ';
        map->spawns[j].pos = (sfVector2f){y + 0.5, x + 0.5};
        switch (buffer[i]){
	  case '^':
	    map->spawns[j].dir = (sfVector2f){-1, 0};
	    map->spawns[j].pln = (sfVector2f){0, 1};
	  break;
	  case '<':
	    map->spawns[j].dir = (sfVector2f){0, -1};
	    map->spawns[j].pln = (sfVector2f){-1, 0};
	  break;
	  case '>':
	    map->spawns[j].dir = (sfVector2f){0, 1};
	    map->spawns[j].pln = (sfVector2f){1, 0};
	  break;
	  case '_':
	    map->spawns[j].dir = (sfVector2f){1, 0};
	    map->spawns[j].pln = (sfVector2f){0, -1};
	  break;
	}

        j++;
      }

      x++;
    }
  }

  return (true);
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