/*
** wolf3d.h for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 10:16:50 2016 Benoit Lormeau
** Last update Tue Dec 13 10:16:54 2016 Benoit Lormeau
*/

#ifndef	WOLF3D_H_
#define	WOLF3D_H_

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>

#define	WIDTH	800
#define	HEIGHT	800

typedef struct	s_framebuffer
{
  sfUint8	*pixels;
  int		width;
  int		height;
}		t_framebuffer;

typedef struct		s_vars
{
  sfVideoMode 		mode;
  sfWindow		*window;
  sfRenderWindow	*rWindow;
  sfSprite 		*sprite;
  sfTexture 		*texture;
  t_framebuffer 	*framebuffer;
}			t_vars;

typedef struct	s_map{
  int		**map;
  int		width;
  int		height;
}		t_map;

double		degrees(double radians);
double		radians(double degrees);
char		*mem_allocat(char *a, char *b);
char		*my_strdup(char *str);
void		get_map(t_map *map, char *mapPath);
char		*get_map_buffer(char *path);
int		get_map_height(char *buffer);
int		get_map_width(char *buffer);
void		fill_map(char *buffer, t_map *map);
void		empty_framebuffer(t_framebuffer *fb);
void		my_put_pixel(t_framebuffer *fb, int x, int y, sfColor color);
void		my_draw_line(t_framebuffer *fb, sfVector2f from, sfVector2f to, sfColor color);
void		my_put_square(t_framebuffer *fb, sfIntRect square, sfColor color);
sfVector2f	move_forward(sfVector2f pos, float direction, float distance);

#endif