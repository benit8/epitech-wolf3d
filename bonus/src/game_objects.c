/*
** game_objects.c for wolf3d in /home/benito/delivery/wolf3d/bonus
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Sun Dec 18 18:54:38 2016 Benoit Lormeau
** Last update Sun Dec 18 18:54:41 2016 Benoit Lormeau
*/

#include "my.h"
#include "wolf3d.h"

int	get_gos(t_map *map, t_gos *gos)
{
  int	i;

  gos->count = 0;
  for (int y = 0; y < map->height; ++y){
    for (int x = 0; x < map->width; ++x){
      if (is_lowercase(map->map[y][x])){
	gos->count++;
      }
    }
  }

  gos->gos = malloc(sizeof(t_go) * gos->count);
  if (gos->gos == NULL) return (0);

  i = 0;
  for (int y = 0; y < map->height; ++y){
    for (int x = 0; x < map->width; ++x){
      if (is_lowercase(map->map[y][x])){
	gos->gos[i].x = y + 0.5;
	gos->gos[i].y = x + 0.5;
	gos->gos[i].texture = get_go_index(map->map[y][x]);
	gos->gos[i].type = 0;
	map->map[y][x] = ' ';
	i++;
      }
    }
  }

  return (1);
}

t_gos	*merge_gos_ents(t_gos *gos, t_ents *ents, t_plyr *player)
{
  t_gos	*res;
  int	i;
  float	tex;
  float	val;
  float	x, y;
  float	ax, ay;

  i = 0;
  tex = 0;
  res = malloc(sizeof(t_gos));
  res->count = gos->count + ents->count;
  res->gos = malloc(sizeof(t_go) * res->count);

  for (int j = 0; j < gos->count; ++j)
    res->gos[i++] = gos->gos[j];

  for (int j = 0; j < ents->count; ++j){
    if (ents->ents[j].hp > 0){
      x = POS.x - ents->ents[j].pos.x;
      y = POS.y - ents->ents[j].pos.y;
      ax = x * ents->ents[j].dir.x + y * ents->ents[j].dir.y;
      ay = x * ents->ents[j].dir.y - y * ents->ents[j].dir.x;

      val = atan2(ay, ax);
      tex = my_map(val, -M_PI, M_PI, 0, 8);
      if (tex >= 7.5)
        tex = 0;

      if (ents->ents[j].run != 0){
        ents->ents[j].run++;

        ents->ents[j].pos.x -= ents->ents[j].dir.x * 0.075;
        ents->ents[j].pos.y -= ents->ents[j].dir.y * 0.075;

        if (ents->ents[j].run > 4)
          ents->ents[j].run = 0;
      }

      tex = round(tex) + (10 * ents->ents[j].run);
    }
    else if (ents->ents[j].hp <= 0 && ents->ents[j].hp >= -5){
      if (ents->ents[j].hp > -5)
        ents->ents[j].hp--;
      tex = (float) (-ents->ents[j].hp + 100);
    }

    res->gos[i++] = (t_go){ents->ents[j].pos.x, ents->ents[j].pos.y, (int) tex, 1};
  }

  return (res);
}

void		go_sort(int *order, double *dist, int amount)
{
  double	d_tmp;
  int		swapped;
  int		i_tmp;
  int		gap;
  int		i;
  int		j;

  gap = amount;
  swapped = 0;
  while (gap > 1 || swapped)
  {
    gap = (gap * 10) / 13;

    if (gap == 9 || gap == 10)
      gap = 11;
    if (gap < 1)
      gap = 1;

    swapped = 0;

    for (i = 0; i < amount - gap; i++){
      j = i + gap;

      if (dist[i] < dist[j]){
	d_tmp = dist[i];
	dist[i] = dist[j];
	dist[j] = d_tmp;

	i_tmp = order[i];
	order[i] = order[j];
	order[j] = i_tmp;
	swapped = 1;
      }
    }
  }
}