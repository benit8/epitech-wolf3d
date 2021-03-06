/*
** entities.c for wolf3d in /home/benito/delivery/wolf3d/bonus
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 20 12:02:45 2016 Benoit Lormeau
** Last update Tue Dec 20 12:02:45 2016 Benoit Lormeau
*/

#include "my.h"
#include "wolf3d.h"

int	get_ents(t_map *map, t_ents *ents)
{
  int	i;

  ents->count = 0;
  for (int y = 0; y < map->height; ++y){
    for (int x = 0; x < map->width; ++x){
      if (is_numeric(map->map[y][x])){
	ents->count++;
      }
    }
  }

  ents->count += 8;
  ents->ents = malloc(sizeof(t_ent) * ents->count);
  if (ents->ents == NULL) return (0);

  i = 0;
  for (int y = 0; y < map->height; ++y){
    for (int x = 0; x < map->width; ++x){
      if (is_numeric(map->map[y][x])){
	ents->ents[i].pos = (sfVector2f){y + 0.5, x + 0.5};
	ents->ents[i].dir = (sfVector2f){-1, 0};
	ents->ents[i].id = -1;
	ents->ents[i].texture = get_ent_index(map->map[y][x]);
	ents->ents[i].run = 0;
	ents->ents[i].shoot = 0;
	ents->ents[i].hp = 100;
	map->map[y][x] = ' ';
	i++;
      }
    }
  }

  for (int id = 0; i < ents->count; ++i){
    ents->ents[i].pos = (sfVector2f){0.5, 0.5};
    ents->ents[i].dir = (sfVector2f){-1, 0};
    ents->ents[i].id = id++;
    ents->ents[i].texture = 0;
    ents->ents[i].run = 0;
    ents->ents[i].shoot = 0;
    ents->ents[i].hp = 100;
  }

  return (1);
}

int	ents_findIndexById(t_ents *ents, sfInt8 id)
{
  for (int i = 0; i < ents->count; ++i){
    if (ents->ents[i].id == id)
      return (i);
  }

  return (-1);
}