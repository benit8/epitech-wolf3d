/*
** states.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Thu Dec 15 15:24:20 2016 Benoit Lormeau
** Last update Thu Dec 15 15:24:34 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	init_states(t_vars *vars)
{
  vars->mapPlyrStates = malloc(sizeof(sfRenderStates));
  vars->mapPlyrStates->blendMode = sfBlendNone;
  vars->mapPlyrStates->transform = sfTransform_Identity;
  vars->mapPlyrStates->texture = NULL;
  vars->mapPlyrStates->shader = NULL;
}