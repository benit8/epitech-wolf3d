/*
** inputs.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 16:16:24 2016 Benoit Lormeau
** Last update Tue Dec 13 16:16:31 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	keyboard(sfKeyCode keyCode, t_map *map, t_vars *vars)
{
  if (keyCode == sfKeyEscape)
    sfRenderWindow_close(vars->rWindow);
  if (keyCode == sfKeyZ || keyCode == sfKeyUp)
    move_player_forward(map);
  if (keyCode == sfKeyS || keyCode == sfKeyDown)
    move_player_backward(map);
  if (keyCode == sfKeyD || keyCode == sfKeyRight)
    move_player_right(map);
    // rotate_player(map, -ROT_SPEED);
  if (keyCode == sfKeyQ || keyCode == sfKeyLeft)
    move_player_left(map);
    // rotate_player(map, ROT_SPEED);
}

void		mouse(sfVector2i mouse, t_map *map, t_vars *vars)
{
  static int	i = 0;
  float		x;

  if (i % 50 && i != 0)
    {
      x = (WIDTH / 2) - mouse.x;
      rotate_player(map, x / (MOUSE_SENS * 2));
      sfMouse_setPositionRenderWindow((sfVector2i){WIDTH / 2, HEIGHT / 2},
      				      vars->rWindow);
    }
  i++;
}