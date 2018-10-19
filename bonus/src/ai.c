/*
** ai.c for wolf3d in /home/benito/delivery/wolf3d/bonus
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Wed Dec 21 14:08:09 2016 Benoit Lormeau
** Last update Wed Dec 21 14:08:10 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void		ai(t_plyr *player, t_ents *ents)
{
  sfVector2f	direction;
  sfVector2f	vDiff;
  float		invLen;
  float		angle;
  float		range;
  float		dot;

  angle = 0.5;
  for (int i = 0; i < ents->count; ++i){
    range = dist(player->pos, ents->ents[i].pos);
    vDiff = (sfVector2f){ents->ents[i].pos.x - POS.x, ents->ents[i].pos.y - POS.y};
    invLen = 1 / sqrt(pow(vDiff.x, 2) + pow(vDiff.y, 2));
    direction = (sfVector2f){vDiff.x * invLen, vDiff.y * invLen};
    dot = (ents->ents[i].dir.x * direction.x + ents->ents[i].dir.y * direction.y);

    if (range < 8)
    {
      if (dot >= cos(M_PI / 12)){
	if (range > 2.5 && ents->ents[i].run == 0)
	  ents->ents[i].run = 1;
	else
	  ents->ents[i].shoot = 1;
      }
      else {
        if (vDiff.y < 0) angle *= -1;
	ents->ents[i].dir = (sfVector2f){ents->ents[i].dir.x * cos(angle) - ents->ents[i].dir.y * sin(angle),
					 ents->ents[i].dir.x * sin(angle) + ents->ents[i].dir.y * cos(angle)};
      }
    }
  }
}