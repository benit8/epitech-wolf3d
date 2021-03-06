/*
** wolf3d.h for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 10:16:50 2016 Benoit Lormeau
** Last update Thu Jan  5 14:23:28 2017 Benoit Lormeau
*/

#ifndef	WOLF3D_H_
# define WOLF3D_H_

# include <stdlib.h>
# include <math.h>
# include <SFML/Graphics/RenderWindow.h>
# include <SFML/Graphics/Texture.h>
# include <SFML/Graphics/Sprite.h>

typedef struct	s_my_framebuffer
{
  sfUint8	*pixels;
  int		width;
  int		height;
}		t_my_framebuffer;

void	my_put_pixel(t_my_framebuffer *, int, int, sfColor);
void	my_draw_line(t_my_framebuffer *, sfVector2i, sfVector2i, sfColor);
sfVector2f	move_forward(sfVector2f, float, float);
float	raycast(sfVector2f, float, int **, sfVector2i);

#endif