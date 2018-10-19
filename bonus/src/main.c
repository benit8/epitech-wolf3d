/*
** main.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Mon Dec 12 19:52:31 2016 Benoit Lormeau
** Last update Mon Dec 12 19:52:33 2016 Benoit Lormeau
*/

#include "my.h"
#include "wolf3d.h"

int	init(t_vars *vars, t_map *map, t_gos *gos, t_plyr *player, t_ents *ents)
{
  if (!get_map(map, player))	return (0);
  if (!get_gos(map, gos))	return (0);
  if (!get_ents(map, ents))	return (0);

  vars->mode.width = WIDTH;
  vars->mode.height = HEIGHT;
  vars->mode.bitsPerPixel = 32;
  vars->framebuffer = malloc(sizeof(t_my_framebuffer));
  vars->framebuffer->pixels = malloc(4 * WIDTH * HEIGHT);
  vars->framebuffer->width = WIDTH;
  vars->framebuffer->height = HEIGHT;
  vars->sprite = sfSprite_create();
  vars->texture = sfTexture_create(WIDTH, HEIGHT);
  vars->mapPlyrStates = malloc(sizeof(sfRenderStates));
  vars->mapPlyrStates->blendMode = sfBlendNone;
  vars->mapPlyrStates->transform = sfTransform_Identity;
  vars->mapPlyrStates->texture = NULL;
  vars->mapPlyrStates->shader = NULL;
  
  if (!load_textures(vars)) return (0);

  vars->rWindow = sfRenderWindow_create(vars->mode, "Call of Benito", sfResize | sfClose, NULL);
  sfRenderWindow_setMouseCursorVisible(vars->rWindow, sfFalse);
  return (1);
}

void	update(t_vars *vars, t_map *map, t_gos *gos, t_plyr *player, t_ents *ents)
{
  sfRenderWindow_clear(vars->rWindow, sfBlack);
  empty_framebuffer(vars->framebuffer);
  ai(player, ents);
  raycast(vars, map, merge_gos_ents(gos, ents, player), player);
  redraw_ui(vars->framebuffer);
  mini_map_player(vars, player, mini_map(vars, map, player));
  sfTexture_updateFromPixels(vars->texture, vars->framebuffer->pixels, WIDTH, HEIGHT, 0, 0);
  sfSprite_setTexture(vars->sprite, vars->texture, sfTrue);
  sfRenderWindow_drawSprite(vars->rWindow, vars->sprite, NULL);
  weapon(vars, player, ents);
  sfRenderWindow_drawVertexArray(vars->rWindow, vars->mapPlyrVertices, vars->mapPlyrStates);
  sfRenderWindow_display(vars->rWindow);
}

int		wolf3d(t_vars *vars, t_map *map, t_gos *gos, t_plyr *player, t_ents *ents)
{
  sfEvent	event;
  sfClock	*timer;

  timer = sfClock_create();
  // music();
  while (sfRenderWindow_isOpen(vars->rWindow))
    {
      while (sfRenderWindow_pollEvent(vars->rWindow, &event))
	{
	  if (event.type == sfEvtClosed)
	    sfRenderWindow_close(vars->rWindow);
	  if (event.type == sfEvtKeyPressed && event.key.code == sfKeyE)
	    switch_weapon(player, 1);
	  if (event.type == sfEvtKeyPressed && event.key.code == sfKeyA)
	    switch_weapon(player, -1);

	  if (event.type == sfEvtMouseMoved)
	    mouse(vars, player, (sfVector2i){event.mouseMove.x, event.mouseMove.y});
	  if (event.type == sfEvtMouseWheelScrolled)
	    switch_weapon(player, event.mouseWheelScroll.delta);
	}
      update(vars, map, gos, player, ents);
      keyboard(vars, map, player, sfClock_getElapsedTime(timer));
      sfClock_restart(timer);
    }
  sfRenderWindow_destroy(vars->rWindow);
  return (0);
}

int		main(int ac, char **av)
{
  t_plyr	*player;
  t_vars	*vars;
  t_ents	*ents;
  t_map		*map;
  t_gos		*gos;

  if (ac < 2) return (84);

  if ((player = malloc(sizeof(t_plyr)))	== NULL)	return (84);
  if ((  vars = malloc(sizeof(t_vars)))	== NULL)	return (84);
  if ((  ents = malloc(sizeof(t_ents)))	== NULL)	return (84);
  if ((   map = malloc(sizeof(t_map)))	== NULL)	return (84);
  if ((   gos = malloc(sizeof(t_gos)))	== NULL)	return (84);

  map->path = strdup(av[1]);
  if (!init(vars, map, gos, player, ents))		return (84);

  wolf3d(vars, map, gos, player, ents);

  free(player);
  free(vars);
  free(ents);
  free(map);
  free(gos);
  return (0);
}
