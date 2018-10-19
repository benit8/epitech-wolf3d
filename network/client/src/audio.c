/*
** audio.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Wed Dec 14 10:28:44 2016 Benoit Lormeau
** Last update Wed Dec 14 10:28:45 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void		music()
{
  sfMusic	*music;

  music = sfMusic_createFromFile("assets/music/e1m1");
  sfMusic_setLoop(music, sfTrue);
  sfMusic_play(music);
}