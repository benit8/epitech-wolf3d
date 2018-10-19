/*
** main.c for wolf3d in /home/benito/delivery/wolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Mon Dec 12 19:52:31 2016 Benoit Lormeau
** Last update Mon Dec 12 19:52:33 2016 Benoit Lormeau
*/

#include "my.h"
#include "wolf3d.h"

int	init(t_vars *vars, t_map *map, t_gos *gos, t_plyr *player, t_ents *ents, t_net *net)
{
  do {
    printf("Enter server IP: ");
    scanf("%s", net->server.address);
  } while (!ip_isValid(net->server.address));

  do {
    printf("Enter server port: ");
    scanf("%hu", &net->port);
  } while (!port_isValid(net->port));

  // strcpy(net->server.address, "10.19.252.252");
  // net->port = 8080;

  srand(time(NULL));

  net->socket = sfTcpSocket_create();
  net->packet = sfPacket_create();

  if (sfTcpSocket_connect(net->socket, net->server, net->port, (sfTime){60000000}) != sfSocketDone)
    error("Couldn't connect to server.");
  printf("Connected to %s:%hu\n", net->server.address, net->port);

  if (sfTcpSocket_receivePacket(net->socket, net->packet) != sfSocketDone)
    error("Couldn't receive identification packet.");
  else if (sfPacket_readInt8(net->packet) == -1)
    error("Room is full. Exiting...");
  else {
    sfPacket_readString(net->packet, map->path);
    sfPacket_clear(net->packet);
  }


  if (!get_map(map, player))	return (0);
  if (!get_gos(map, gos))	return (0);
  if (!get_ents(map, ents))	return (0);

  respawn(player, map, net);
  sfTcpSocket_setBlocking(net->socket, sfFalse);


  vars->mode.width = WIDTH;
  vars->mode.height = HEIGHT;
  vars->mode.bitsPerPixel = 32;
  vars->framebuffer = malloc(sizeof(t_my_framebuffer));
  vars->framebuffer->pixels = malloc(4 * WIDTH * HEIGHT);
  vars->framebuffer->width = WIDTH;
  vars->framebuffer->height = HEIGHT;
  vars->sprite = sfSprite_create();
  vars->texture = sfTexture_create(WIDTH, HEIGHT);
  vars->mapPlyrStates = malloc(sizeof(sfRenderStates));
  vars->mapPlyrStates->blendMode = sfBlendNone;
  vars->mapPlyrStates->transform = sfTransform_Identity;
  vars->mapPlyrStates->texture = NULL;
  vars->mapPlyrStates->shader = NULL;

  vars->fontDead = sfFont_createFromFile("assets/fonts/danksouls.ttf");
  vars->textDead = sfText_create();
  sfText_setFont(vars->textDead, vars->fontDead);
  sfText_setString(vars->textDead, "YOU DIED");
  sfText_setCharacterSize(vars->textDead, 130);
  sfText_setColor(vars->textDead, sfColor_fromRGB(138, 7, 7));
  sfText_setPosition(vars->textDead, (sfVector2f){280, 320});
  
  if (!load_textures(vars)) return (0);

  vars->rWindow = sfRenderWindow_create(vars->mode, "Call of Benito", sfResize | sfClose, NULL);
  sfRenderWindow_setMouseCursorVisible(vars->rWindow, sfFalse);
  return (1);
}

void	update(t_vars *vars, t_map *map, t_gos *gos, t_plyr *player, t_ents *ents, t_net *net)
{
  sfRenderWindow_clear(vars->rWindow, sfBlack);
  empty_framebuffer(vars->framebuffer);
  raycast(vars, map, merge_gos_ents(gos, ents, player), player);
  redraw_ui(vars->framebuffer);
  mini_map_player(vars, player, mini_map(vars, map, player));
  sfTexture_updateFromPixels(vars->texture, vars->framebuffer->pixels, WIDTH, HEIGHT, 0, 0);
  sfSprite_setTexture(vars->sprite, vars->texture, sfTrue);
  sfRenderWindow_drawSprite(vars->rWindow, vars->sprite, NULL);
  if (player->hp > 0)
    weapon(vars, player, ents, net);
  else
    you_died(vars);
  sfRenderWindow_drawVertexArray(vars->rWindow, vars->mapPlyrVertices, vars->mapPlyrStates);
  sfRenderWindow_display(vars->rWindow);
}

int		wolf3d(t_vars *vars, t_map *map, t_gos *gos, t_plyr *player, t_ents *ents, t_net *net)
{
  sfEvent	event;
  sfClock	*timer;

  timer = sfClock_create();
  music();
  while (sfRenderWindow_isOpen(vars->rWindow))
    {
      while (sfRenderWindow_pollEvent(vars->rWindow, &event))
	{
	  if (event.type == sfEvtClosed)
	    sfRenderWindow_close(vars->rWindow);
	  // if (event.type == sfEvtKeyPressed && event.key.code == sfKeyE)
	  //   switch_weapon(player, 1);
	  // if (event.type == sfEvtKeyPressed && event.key.code == sfKeyA)
	  //   switch_weapon(player, -1);

	  // if (event.type == sfEvtMouseMoved)
	  //   mouse(vars, player, (sfVector2i){event.mouseMove.x, event.mouseMove.y}, net);
	  // if (event.type == sfEvtMouseWheelScrolled)
	  //   switch_weapon(player, event.mouseWheelScroll.delta);
	}
      update(vars, map, gos, player, ents, net);
      keyboard(vars, map, player, sfClock_getElapsedTime(timer), net);

      if (sfTcpSocket_receivePacket(net->socket, net->packet) == sfSocketDone)
        update_ents(ents, player, net);

      sfClock_restart(timer);
    }
  sfRenderWindow_destroy(vars->rWindow);
  return (0);
}

int		main(void)
{
  t_plyr	*player;
  t_vars	*vars;
  t_ents	*ents;
  t_map		*map;
  t_gos		*gos;
  t_net		*net;

  if ((player = malloc(sizeof(t_plyr)))	== NULL)	return (84);
  if ((  vars = malloc(sizeof(t_vars)))	== NULL)	return (84);
  if ((  ents = malloc(sizeof(t_ents)))	== NULL)	return (84);
  if ((   map = malloc(sizeof(t_map)))	== NULL)	return (84);
  if ((   gos = malloc(sizeof(t_gos)))	== NULL)	return (84);
  if ((   net = malloc(sizeof(t_net)))	== NULL)	return (84);

  if (!init(vars, map, gos, player, ents, net))		return (85);

  wolf3d(vars, map, gos, player, ents, net);

  free(player);
  free(vars);
  free(ents);
  free(map);
  free(gos);
  free(net);
  return (0);
}
