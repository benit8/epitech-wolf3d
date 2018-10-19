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


////////////////////////////////////////////////////////////////////////////////
// INCLUDEs
////////////////////////////////////////////////////////////////////////////////

# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <sys/stat.h>
# include <SFML/Audio.h>
# include <SFML/Graphics.h>
# include <SFML/Network.h>
# include <SFML/System.h>
# include <SFML/Window.h>


////////////////////////////////////////////////////////////////////////////////
// DEFINEs
////////////////////////////////////////////////////////////////////////////////

# define	WIDTH		1200
# define	HEIGHT		800

# define	UI_H		200

# define	USE_TEXTURE	1
# define	TEXTURE_WIDTH	64
# define	TEXTURE_HEIGHT	64

# define	WEAPON_SCALE	7

# define	MOVE_SPEED	4.0
# define	ROT_SPEED	2.5
# define	MOUSE_SENS	1000

# define	POS		player->pos
# define	DIR		player->dir
# define	PLN		player->plane


////////////////////////////////////////////////////////////////////////////////
// STRUCTUREs
////////////////////////////////////////////////////////////////////////////////

/* SMALLs
***************************************/

// FRAMEBUFFER
typedef struct	s_my_framebuffer
{
  sfUint8	*pixels;
  int		width;
  int		height;
}		t_my_framebuffer;

// SPRITES
typedef struct	s_sprites{
  sfImage	**guard;
  sfImage	**gameObjects;
}		t_sprites;

// TEXTURES
typedef struct	s_textures{
  t_sprites	*sprites;
  sfImage	**walls;
  sfTexture	***weapons;
}		t_textures;

// GAME OBJECT
typedef struct	s_go{
  double	x;
  double	y;
  int		texture;
  char		type;
}		t_go;

// ENTITY
typedef struct	s_ent{
  sfVector2f	pos;
  sfVector2f	dir;
  short		id;
  int		run;
  int		shoot;
  int		texture;
  int		hp;
}		t_ent;

typedef struct	s_spwn{
  sfVector2f	pos;
  sfVector2f	dir;
  sfVector2f	pln;
}		t_spwn;


/* BIGs
***************************************/

// VARIABLES
typedef struct		s_vars
{
  sfVideoMode		mode;
  sfWindow		*window;
  sfRenderWindow	*rWindow;
  sfSprite		*sprite;
  sfTexture		*texture;
  t_textures		*textures;
  t_my_framebuffer	*framebuffer;
  sfRenderStates	*mapPlyrStates;
  sfVertexArray		*mapPlyrVertices;
  sfFont		*fontDead;
  sfText		*textDead;
}			t_vars;

// MAP
typedef struct	s_map{
  char		**map;
  int		width;
  int		height;
  char		path[64];
  t_spwn	*spawns;
  int		spawnCount;
}		t_map;

// GAME OBJECTS
typedef struct	s_gos{
  t_go		*gos;
  int		count;
}		t_gos;

// ENTITIES
typedef struct	s_ents{
  t_ent		*ents;
  int		count;
}		t_ents;

// PLAYER
typedef struct	s_plyr{
  sfVector2f	pos;
  sfVector2f	dir;
  sfVector2f	plane;
  sfVector2f	pos0;
  sfVector2f	dir0;
  sfVector2f	plane0;
  int		hp;
  int		weapon;
  int		isShooting;
}		t_plyr;

// NETWORK
typedef struct		s_net{
  sfTcpSocket		*socket;
  sfPacket		*packet;
  sfIpAddress		server;
  unsigned short	port;
  sfInt8		id;
}			t_net;


////////////////////////////////////////////////////////////////////////////////
// PROTOTYPEs
////////////////////////////////////////////////////////////////////////////////

// MATH UTILS
double		degrees(double);
double		radians(double);
float		my_map(float, float, float, float, float);
float		dist(sfVector2f, sfVector2f);
int		randint(int);

// VECTOR UTILS
sfVector2f	vectCopy(sfVector2f);
sfVector2f	vectAdd(sfVector2f, sfVector2f);
sfVector2f	vectSub(sfVector2f, sfVector2f);
sfVector2f	vectMul(sfVector2f, float);
sfVector2f	vectDiv(sfVector2f, float);
float		vectDistSq(sfVector2f, sfVector2f);
float		vectMag(sfVector2f);
sfVector2f	vectSetMag(sfVector2f, float);
sfVector2f	vectNormalize(sfVector2f);

// MAP
int		get_map(t_map *, t_plyr *);

// INIT
void		init_states(t_vars *);

// TEXTURES
int		load_textures(t_vars *);
int		get_wall_index(char);

// GAME OBJECTS
int		get_gos(t_map *, t_gos *);
int		get_go_index(char);
void		go_sort(int *, double *, int);
t_gos		*merge_gos_ents(t_gos *, t_ents *, t_plyr *);

// ENTITES
int		get_ents(t_map *, t_ents *);
int		get_ent_index(char);
int		ents_findIndexById(t_ents *, sfInt8);

// ARTIFICIAL INTELLIGENCE
void		ai(t_plyr *, t_ents *);

// FRAMEBUFFER
void		empty_framebuffer(t_my_framebuffer *);
void		redraw_ui(t_my_framebuffer *);

void		my_put_pixel(t_my_framebuffer *, int, int, sfColor);
void		my_draw_line(t_my_framebuffer *, sfVector2i, sfVector2i, sfColor);
void		my_put_square(t_my_framebuffer *, sfIntRect, sfColor);
void		raycast(t_vars *, t_map *, t_gos *, t_plyr *);

// PLAYER
void		you_died(t_vars *);
void		respawn(t_plyr *, t_map *, t_net *);

// MOVEMENT
void		move_player_forward(t_map *, t_plyr *, float, t_net *);
void		move_player_backward(t_map *, t_plyr *, float, t_net *);
void		rotate_player(t_plyr *, float, t_net *);

// WEAPONS
void		weapon(t_vars *, t_plyr *, t_ents *, t_net *);
int		shoot(t_plyr *, t_ents *, t_net *);
void		switch_weapon(t_plyr *, float);

// MINI-MAP
sfVector2i	mini_map(t_vars *, t_map *, t_plyr *);
void		mini_map_player(t_vars *, t_plyr *, sfVector2i);

// EVENTS - MUSIC
void		keyboard(t_vars *, t_map *, t_plyr *, sfTime, t_net *);
void		mouse(t_vars *, t_plyr *, sfVector2i, t_net *);
void		music();

// NETWORK
void		error(char *);
bool		ip_isValid(char *);
bool		port_isValid(unsigned short);
void		update_ents(t_ents *, t_plyr *, t_net *);
void		sendPos(t_plyr *, t_net *);
void		sendDir(t_plyr *, t_net *);
void		sendShot(short, t_net *);
void		sendRes(t_net *);

#endif