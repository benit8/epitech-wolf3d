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
# define WOLF3D_H_

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <SFML/Audio.h>
# include <SFML/Graphics.h>
# include <SFML/System.h>
# include <SFML/Window.h>

# define	WIDTH		1200
# define	HEIGHT		800

# define	UI_H		200

# define	MOVE_SPEED	0.1
# define	ROT_SPEED	0.05
# define	MOUSE_SENS	100

# define	POS		map->plyrPos
# define	DIR		map->plyrDir

typedef struct	s_my_framebuffer
{
  sfUint8	*pixels;
  int		width;
  int		height;
}		t_my_framebuffer;

typedef struct		s_vars
{
  sfVideoMode		mode;
  sfWindow		*window;
  sfRenderWindow	*rWindow;
  sfSprite		*sprite;
  sfTexture		*texture;
  sfRenderStates	*mapPlyrStates;
  sfVertexArray		*mapPlyrVertices;
  t_my_framebuffer	*framebuffer;
}			t_vars;

typedef struct	s_map{
  int		**map;
  int		width;
  int		height;
  sfVector2f	plyrPos;
  sfVector2f	plyrDir;
  sfVector2f	plane;
}		t_map;

typedef struct	s_raycast{
  sfColor	color;
  double	camera;
  double	rayPosX;
  double	rayPosY;
  double	rayDirX;
  double	rayDirY;
  double	sideDistX;
  double	sideDistY;
  double	deltaDistX;
  double	deltaDistY;
  double	perpWallDist;
  int		mapX;
  int		mapY;
  int		lineHeight;
  int		drawStart;
  int		drawEnd;
  int		stepX;
  int		stepY;
  int		side;
  int		hit;
}		t_raycast;

double		degrees(double radians);
double		radians(double degrees);
float		my_map(float n, float start1, float stop1, float start2, float stop2);

char		*my_strdup(char *str);
char		*mem_allocat(char *a, char *b);

int		get_map(t_map *map, char *mapPath);
char		*get_map_buffer(char *path);
int		get_map_height(char *buffer);
int		get_map_width(char *buffer);
void		fill_map(char *buffer, t_map *map);
sfVector2f	find_player_pos(t_map *map);

void		init_states(t_vars *vars);

void		empty_framebuffer(t_my_framebuffer *fb);
void		redraw_framebuffer(t_my_framebuffer *fb);
void		redraw_ui(t_my_framebuffer *fb);

void		my_put_pixel(t_my_framebuffer *fb, int x, int y, sfColor color);
void		my_draw_line(t_my_framebuffer *fb,
			     sfVector2i from,
			     sfVector2i to,
			     sfColor color);
void		my_put_square(t_my_framebuffer *fb, 
			      sfIntRect sqr,
			      sfColor color);
sfVector2f	move_forward(sfVector2f pos, float direction, float distance);
float		raycast(sfVector2f pos,
			float direction,
			int **map,
			sfVector2i mapSize);

void		move_player_forward(t_map *map);
void		move_player_backward(t_map *map);
void		move_player_right(t_map *map);
void		move_player_left(t_map *map);
void		rotate_player(t_map *map, float speed);

void		raycasting(t_my_framebuffer *fb, t_map *map);
sfVector2i	mini_map(t_vars *vars, t_map *map);
void		mini_map_player(t_vars *vars, t_map *map, sfVector2i pos);
void		cross(t_my_framebuffer *fb);

void		keyboard(sfKeyCode keyCode, t_map *map, t_vars *vars);
void		mouse(sfVector2i mouse, t_map *map, t_vars *vars);
void		music();

#endif