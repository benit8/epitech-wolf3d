/*
** weapon.c for wolf3d in /home/benito/delivery/wolf3d/bonus
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Sat Dec 17 00:08:02 2016 Benoit Lormeau
** Last update Sat Dec 17 00:08:03 2016 Benoit Lormeau
*/

#include "textures.h"
#include "wolf3d.h"

void		weapon(t_vars *vars, t_plyr *player, t_ents *ents, t_net *net)
{
  sfTransform	transform;

  transform = sfTransform_Identity;
  sfTransform_translate(&transform, (WIDTH           - (64 * WEAPON_SCALE)) / 2,
  				    ((HEIGHT - UI_H) - (64 * WEAPON_SCALE)));
  sfTransform_scale(&transform, WEAPON_SCALE, WEAPON_SCALE);

  if (player->isShooting > 0)
    sfSprite_setTexture(vars->sprite, vars->textures->weapons[player->weapon][player->isShooting], sfTrue);
  else
    sfSprite_setTexture(vars->sprite, vars->textures->weapons[player->weapon][0], sfTrue);

  if (player->isShooting != 0){
    player->isShooting++;

    if (player->isShooting == 3)
      shoot(player, ents, net);

    if (player->weapon == 3 && player->isShooting == 4 && (sfKeyboard_isKeyPressed(sfKeySpace) || sfMouse_isButtonPressed(sfMouseLeft)))
      player->isShooting = 2;		// Special gatling loop
    else{
      if (player->isShooting > 4){
	if (player->weapon == 0)	// Knife delay
	  player->isShooting = -5;
	else if (player->weapon == 1)	// Gun delay
	  player->isShooting = -10;
	else
    	  player->isShooting = ((sfKeyboard_isKeyPressed(sfKeySpace) || sfMouse_isButtonPressed(sfMouseLeft))) ? 2 : 0;
      }
    }
  }

  sfRenderWindow_drawSprite(vars->rWindow, vars->sprite, &(sfRenderStates){sfBlendAlpha, transform, NULL, NULL});
}

int		shoot(t_plyr *player, t_ents *ents, t_net *net)
{
  sfVector2f	direction;
  sfVector2f	vDiff;
  float		invLen;
  float		range;
  float		dot;

  for (int i = 0; i < ents->count; ++i){
    range = dist(player->pos, ents->ents[i].pos);
    if (range < 8){
      vDiff = (sfVector2f){ents->ents[i].pos.x - POS.x, ents->ents[i].pos.y - POS.y};
      invLen = 1 / sqrt(pow(vDiff.x, 2) + pow(vDiff.y, 2));
      direction = (sfVector2f){vDiff.x * invLen, vDiff.y * invLen};
      dot = (DIR.x * direction.x + DIR.y * direction.y);

      if (dot > 0.98 && ents->ents[i].hp > 0){
        if ((player->weapon == 0 && range <= 1.5) || player->weapon > 0){
          ents->ents[i].hp = 0;
          sendShot(ents->ents[i].id, net);
        }
        return (0);
      }
    }
  }

  return (1);
}

void	switch_weapon(t_plyr *player, float delta)
{
  player->weapon -= (int) delta;

  if (player->weapon < 0) player->weapon = 0;
  if (player->weapon > 3) player->weapon = 3;
}