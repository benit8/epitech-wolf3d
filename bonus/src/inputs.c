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

void	keyboard(t_vars *vars, t_map *map, t_plyr *player, sfTime time)
{
  float	sec = sfTime_asSeconds(time);

  if (sfKeyboard_isKeyPressed(sfKeyEscape))
    sfRenderWindow_close(vars->rWindow);

  if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyUp))
    move_player_forward(map, player, sec);
  if (sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown))
    move_player_backward(map, player, sec);
  if ((sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight)) && !sfKeyboard_isKeyPressed(sfKeyQ) && !sfKeyboard_isKeyPressed(sfKeyLeft))
    rotate_player(player, -ROT_SPEED * sec);
  if ((sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyLeft)) && !sfKeyboard_isKeyPressed(sfKeyD) && !sfKeyboard_isKeyPressed(sfKeyRight))
    rotate_player(player, ROT_SPEED * sec);

  if ((sfKeyboard_isKeyPressed(sfKeySpace) || sfMouse_isButtonPressed(sfMouseLeft)) && player->isShooting == 0)
    player->isShooting = 1;
}

void		mouse(t_vars *vars, t_plyr *player, sfVector2i mouse)
{
  static int	i;
  float		x;

  if (i % 50 && i != 0)
    {
      x = (WIDTH / 2) - mouse.x;
      rotate_player(player, x / MOUSE_SENS);
      sfMouse_setPositionRenderWindow((sfVector2i){WIDTH / 2, HEIGHT / 2},
      				      vars->rWindow);
    }
  i++;
}