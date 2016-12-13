/*
** main.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Mon Dec 12 19:52:31 2016 Benoit Lormeau
** Last update Mon Dec 12 19:52:33 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	init(t_vars *vars, t_map *map, char *mapPath)
{
  get_map(map, mapPath);
  vars->mode.width = WIDTH;
  vars->mode.height = HEIGHT;
  vars->mode.bitsPerPixel = 32;
  vars->framebuffer = malloc(sizeof(t_framebuffer));
  vars->framebuffer->pixels = malloc(4 * WIDTH * HEIGHT);
  vars->framebuffer->width = WIDTH;
  vars->framebuffer->height = HEIGHT;
  empty_framebuffer(vars->framebuffer);
  vars->sprite = sfSprite_create();
  vars->texture = sfTexture_create(WIDTH, HEIGHT);
  sfTexture_updateFromPixels(vars->texture, vars->framebuffer->pixels,
  			     WIDTH, HEIGHT, 0, 0);
  sfSprite_setTexture(vars->sprite, vars->texture, sfTrue);
  vars->rWindow = sfRenderWindow_create(vars->mode, "Bootstrap Wolf3D",
  					sfResize | sfClose, NULL);
}

int		main(int ac, char **av)
{
  t_vars	*vars;
  t_map		*map;
  sfEvent	event;

  if (ac < 2)
     return (84);
  vars = malloc(sizeof(t_vars));
  map = malloc(sizeof(t_map));
  init(vars, map, av[1]);
  if (vars == NULL || map == NULL)
    return (84);
  while (sfRenderWindow_isOpen(vars->rWindow))
    {
      while (sfRenderWindow_pollEvent(vars->rWindow, &event))
	{
	  if (event.type == sfEvtClosed)
	    sfRenderWindow_close(vars->rWindow);
	  if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
	    sfRenderWindow_close(vars->rWindow);
	}
      sfRenderWindow_clear(vars->rWindow, sfBlack);
      sfRenderWindow_drawSprite(vars->rWindow, vars->sprite, NULL);
      sfRenderWindow_display(vars->rWindow);
    }
  sfRenderWindow_destroy(vars->rWindow);
  free(vars->framebuffer);
  return (0);
}
