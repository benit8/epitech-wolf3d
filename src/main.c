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

int	init(t_vars *vars, t_map *map, char *mapPath)
{
  if (!get_map(map, mapPath))
    return (0);
  vars->mode.width = WIDTH;
  vars->mode.height = HEIGHT;
  vars->mode.bitsPerPixel = 32;
  vars->framebuffer = malloc(sizeof(t_my_framebuffer));
  vars->framebuffer->pixels = malloc(4 * WIDTH * HEIGHT);
  vars->framebuffer->width = WIDTH;
  vars->framebuffer->height = HEIGHT;
  vars->sprite = sfSprite_create();
  vars->texture = sfTexture_create(WIDTH, HEIGHT);
  init_states(vars);
  sfTexture_updateFromPixels(vars->texture, vars->framebuffer->pixels,
  			     WIDTH, HEIGHT, 0, 0);
  sfSprite_setTexture(vars->sprite, vars->texture, sfTrue);
  vars->rWindow = sfRenderWindow_create(vars->mode, "Wolf3D",
  					sfResize | sfClose, NULL);
  sfRenderWindow_setMouseCursorVisible(vars->rWindow, sfFalse);
  return (1);
}

void	update(t_vars *vars, t_map *map)
{
  sfRenderWindow_clear(vars->rWindow, sfWhite);
  redraw_framebuffer(vars->framebuffer);
  raycasting(vars->framebuffer, map);
  cross(vars->framebuffer);
  redraw_ui(vars->framebuffer);
  mini_map_player(vars, map, mini_map(vars, map));
  sfTexture_updateFromPixels(vars->texture, vars->framebuffer->pixels, WIDTH, HEIGHT, 0, 0);
  sfSprite_setTexture(vars->sprite, vars->texture, sfTrue);
  sfRenderWindow_drawSprite(vars->rWindow, vars->sprite, NULL);
  sfRenderWindow_drawVertexArray(vars->rWindow, vars->mapPlyrVertices, vars->mapPlyrStates);
  sfRenderWindow_display(vars->rWindow);
}

int		wolf3d(t_vars *vars, t_map *map)
{
  sfEvent	event;

  music();
  while (sfRenderWindow_isOpen(vars->rWindow))
    {
      while (sfRenderWindow_pollEvent(vars->rWindow, &event))
	{
	  if (event.type == sfEvtClosed)
	    sfRenderWindow_close(vars->rWindow);
	  if (event.type == sfEvtKeyPressed)
	    keyboard(event.key.code, map, vars);
	  if (event.type == sfEvtMouseMoved)
	    mouse((sfVector2i){event.mouseMove.x, event.mouseMove.y}, map, vars);
	}
      update(vars, map);
    }
  sfRenderWindow_destroy(vars->rWindow);
  return (0);
}

int		main(int ac, char **av)
{
  t_vars	*vars;
  t_map		*map;

  if (ac < 2)
     return (84);
  if ((vars = malloc(sizeof(t_vars))) == NULL)
    return (84);
  if ((map = malloc(sizeof(t_map))) == NULL)
    return (84);
  if (!init(vars, map, av[1]))
    return (84);
  wolf3d(vars, map);
  free(vars);
  free(map);
  return (0);
}
