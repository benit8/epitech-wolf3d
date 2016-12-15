/*
** raycast.c for bswolf3d in /home/benito/delivery/bswolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 00:04:38 2016 Benoit Lormeau
** Last update Tue Dec 13 00:04:49 2016 Benoit Lormeau
*/

#include "wolf3d.h"

void	raycast_slave_1(t_raycast *rc);
void	raycast_slave_2(t_raycast *rc, t_map *map);
void	raycast_slave_3(t_raycast *rc);
void	raycast_dda(t_raycast *rc, t_map *map);

void
raycasting(t_my_framebuffer *fb, t_map *map)
{
  t_raycast	*rc;
  int		x;

  x = -1;
  while (++x < WIDTH)
    {
      rc = malloc(sizeof(t_raycast));
      rc->camera = 2 * x / (double) WIDTH - 1;
      rc->rayPosX = map->plyrPos.x;
      rc->rayPosY = map->plyrPos.y;
      rc->rayDirX = map->plyrDir.x + map->plane.x * rc->camera;
      rc->rayDirY = map->plyrDir.y + map->plane.y * rc->camera;
      rc->mapX = (int) rc->rayPosX;
      rc->mapY = (int) rc->rayPosY;
      rc->deltaDistX = sqrt(1 + (rc->rayDirY * rc->rayDirY) /
      				(rc->rayDirX * rc->rayDirX));
      rc->deltaDistY = sqrt(1 + (rc->rayDirX * rc->rayDirX) /
      				(rc->rayDirY * rc->rayDirY));
      raycast_slave_1(rc);
      raycast_dda(rc, map);
      raycast_slave_2(rc, map);
      my_draw_line(fb, (sfVector2i){x, rc->drawStart},
      	               (sfVector2i){x, rc->drawEnd}, rc->color);
      free(rc);
    }
}

void
raycast_slave_1(t_raycast *rc)
{
  rc->hit = 0;
  if (rc->rayDirX < 0)
    {
      rc->stepX = -1;
      rc->sideDistX = (rc->rayPosX - rc->mapX) * rc->deltaDistX;
    }
  else
    {
      rc->stepX = 1;
      rc->sideDistX = (rc->mapX + 1.0 - rc->rayPosX) * rc->deltaDistX;
    }
  if (rc->rayDirY < 0)
    {
      rc->stepY = -1;
      rc->sideDistY = (rc->rayPosY - rc->mapY) * rc->deltaDistY;
    }
  else
    {
      rc->stepY = 1;
      rc->sideDistY = (rc->mapY + 1.0 - rc->rayPosY) * rc->deltaDistY;
    }
}

void
raycast_dda(t_raycast *rc, t_map *map)
{
  while (rc->hit == 0)
    {
      if (rc->sideDistX < rc->sideDistY)
        {
          rc->sideDistX += rc->deltaDistX;
          rc->mapX += rc->stepX;
          rc->side = 0;
        }
      else
        {
          rc->sideDistY += rc->deltaDistY;
          rc->mapY += rc->stepY;
          rc->side = 1;
        }
      if (map->map[rc->mapX][rc->mapY] > 0)
        rc->hit = 1;
    }
}

void
raycast_slave_2(t_raycast *rc, t_map *map)
{
  if (rc->side == 0)
    rc->perpWallDist = (rc->mapX - rc->rayPosX + (1 - rc->stepX) / 2) /
			rc->rayDirX;
  else
    rc->perpWallDist = (rc->mapY - rc->rayPosY + (1 - rc->stepY) / 2) /
			rc->rayDirY;
  rc->lineHeight = (int)((HEIGHT - UI_H) / rc->perpWallDist);
  rc->drawStart = -rc->lineHeight / 2 + (HEIGHT - UI_H) / 2;
  if (rc->drawStart < 0)
    rc->drawStart = 0;
  rc->drawEnd = rc->lineHeight / 2 + (HEIGHT - UI_H) / 2;
  if (rc->drawEnd >= (HEIGHT - UI_H))
    rc->drawEnd = (HEIGHT - UI_H) - 1;
  if (map->map[rc->mapX][rc->mapY] == 1)
    rc->color = sfRed;
  else if (map->map[rc->mapX][rc->mapY] == 2)
    rc->color = sfBlue;
  else if (map->map[rc->mapX][rc->mapY] == 3)
    rc->color = sfGreen;
  else if (map->map[rc->mapX][rc->mapY] == 4)
    rc->color = sfYellow;
  else
    rc->color = sfBlack;
  if (rc->side)
    raycast_slave_3(rc);
}

void
raycast_slave_3(t_raycast *rc)
{
  rc->color.r /= 2;
  rc->color.g /= 2;
  rc->color.b /= 2;
}