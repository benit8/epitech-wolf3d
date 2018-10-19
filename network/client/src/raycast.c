/*
** raycast.c for bswolf3d in /home/benito/delivery/bswolf3d
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Tue Dec 13 00:04:38 2016 Benoit Lormeau
** Last update Tue Dec 13 00:04:49 2016 Benoit Lormeau
*/

#include "my.h"
#include "wolf3d.h"

void	raycast(t_vars *vars, t_map *map, t_gos *gos, t_plyr *player)
{
  sfColor	color;
  double	camera;
  double	rayPosX, rayPosY;
  double	rayDirX, rayDirY;
  double	deltaDistX, deltaDistY;
  double	ZBuffer[WIDTH];
  int		mapX, mapY;
  int		a;
  int		h;
  int		y;

  h = (HEIGHT - UI_H);

  for (int x = 0; x < WIDTH; ++x){
    camera = 2 * x / (double) WIDTH - 1;
    rayPosX = player->pos.x;
    rayPosY = player->pos.y;
    rayDirX = player->dir.x + player->plane.x * camera;
    rayDirY = player->dir.y + player->plane.y * camera;
    mapX = (int) rayPosX;
    mapY = (int) rayPosY;
    deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
    deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

    
    ////////////////////////////////////////////////////////////////////////////
    // WALLS
    ////////////////////////////////////////////////////////////////////////////

    double	wallX;
    double	perpWallDist;
    double	sideDistX, sideDistY;
    int		drawStart, drawEnd;
    int		stepX, stepY;
    int		texX, texY;
    int		lineHeight;
    int		texNum;
    int		side;
    int		hit;


    hit = 0;
    if (rayDirX < 0){
      stepX = -1;
      sideDistX = (rayPosX - mapX) * deltaDistX;
    } else{
      stepX = 1;
      sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
    }

    if (rayDirY < 0){
      stepY = -1;
      sideDistY = (rayPosY - mapY) * deltaDistY;
    } else{
      stepY = 1;
      sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
    }

    // DDA
    while (hit == 0){
      if (sideDistX < sideDistY){
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;
      } else{
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;
      }

      if (map->map[mapX][mapY] != ' ') hit = 1;
    }

    if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
    else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

    lineHeight = (int)(h / perpWallDist);

    drawStart = -lineHeight / 2 + h / 2;
    drawEnd   =  lineHeight / 2 + h / 2;
    if (drawStart < 0)              drawStart = 0;
    if (drawEnd >= h) drawEnd = h - 1;

    // TEXTURE
    texNum = get_wall_index(map->map[mapX][mapY]);

    if (side == 0) wallX = rayPosY + perpWallDist * rayDirY;
    else           wallX = rayPosX + perpWallDist * rayDirX;
    wallX -= floor((wallX));

    texX = (int) (wallX * (double) TEXTURE_WIDTH);
    if (side == 0 && rayDirX > 0) texX = TEXTURE_WIDTH - texX - 1;
    if (side == 1 && rayDirY < 0) texX = TEXTURE_WIDTH - texX - 1;

    for (y = drawStart; y < drawEnd; y++){
      a = y * 256 - h * 128 + lineHeight * 128;
      texY = ((a * TEXTURE_HEIGHT) / lineHeight) / 256;
      color = sfImage_getPixel(vars->textures->walls[texNum], texX, texY);
      
      if (side){
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
      }

      my_put_pixel(vars->framebuffer, x, y, color);
    }


    ////////////////////////////////////////////////////////////////////////////
    // FLOOR - CEILING
    ////////////////////////////////////////////////////////////////////////////

    double	weight;
    double	distWall;
    double	distPlayer;
    double	currentDist;
    double	floorXWall, floorYWall;
    double	currentFloorX, currentFloorY;
    int		floorTexX, floorTexY;


    ZBuffer[x] = perpWallDist;

    if (side == 0 && rayDirX > 0) {
      floorXWall = mapX;
      floorYWall = mapY + wallX; }
    else if (side == 0 && rayDirX < 0) {
      floorXWall = mapX + 1.0;
      floorYWall = mapY + wallX; }
    else if (side == 1 && rayDirY > 0) {
      floorXWall = mapX + wallX;
      floorYWall = mapY; }
    else {
      floorXWall = mapX + wallX;
      floorYWall = mapY + 1.0; }

    distWall = perpWallDist;
    distPlayer = 0.0;
    if (drawEnd < 0)
      drawEnd = h;

    for (int y = drawEnd + 1; y < h; ++y){
      currentDist = h / (2.0 * y - h);
      weight = (currentDist - distPlayer) / (distWall - distPlayer);
      currentFloorX = weight * floorXWall + (1.0 - weight) * player->pos.x;
      currentFloorY = weight * floorYWall + (1.0 - weight) * player->pos.y;
      floorTexX = (int) (currentFloorX * TEXTURE_WIDTH) % TEXTURE_WIDTH;
      floorTexY = (int) (currentFloorY * TEXTURE_HEIGHT) % TEXTURE_HEIGHT;

      color = sfImage_getPixel(vars->textures->walls[1], floorTexX, floorTexY);
      color.r /= 2; color.g /= 2; color.b /= 2;
      my_put_pixel(vars->framebuffer, x, y - 1, color);

      color = sfImage_getPixel(vars->textures->walls[1], floorTexX, floorTexY);
      my_put_pixel(vars->framebuffer, x, h - y, color);
    }
  }


  ////////////////////////////////////////////////////////////////////////////
  // SPRITES
  ////////////////////////////////////////////////////////////////////////////

  double	invDet;
  double	spriteX, spriteY;
  double	transformX, transformY;
  double	spriteDistance[gos->count];
  int		spriteWidth, spriteHeight;
  int		spriteOrder[gos->count];
  int		drawStartX, drawStartY;
  int		drawEndX, drawEndY;
  int		spriteScreenX;
  int		texX, texY;
  int		stripe;
  int		i;


  for (i = 0; i < gos->count; ++i){
    spriteOrder[i] = i;
    spriteDistance[i] = ((POS.x - gos->gos[i].x) * (POS.x - gos->gos[i].x) + (POS.y - gos->gos[i].y) * (POS.y - gos->gos[i].y));
  }

  go_sort(spriteOrder, spriteDistance, gos->count);

  for (i = 0; i < gos->count; ++i){
    spriteX = gos->gos[spriteOrder[i]].x - POS.x;
    spriteY = gos->gos[spriteOrder[i]].y - POS.y;

    invDet = 1.0 / (PLN.x * DIR.y - DIR.x * PLN.y);
    transformX = invDet * (DIR.y * spriteX - DIR.x * spriteY);
    transformY = invDet * (-PLN.y * spriteX + PLN.x * spriteY);
    spriteScreenX = (int) ((WIDTH / 2) * (1 + transformX / transformY));
    spriteHeight = abs( (int) (h / (transformY)) );
    spriteWidth  = abs( (int) (h / (transformY)) );

    drawStartY = -spriteHeight / 2 + h / 2;
    drawEndY   =  spriteHeight / 2 + h / 2;
    if (drawStartY < 0)
      drawStartY = 0;
    if (drawEndY >= h)
      drawEndY = h - 1;

    drawStartX = -spriteWidth / 2 + spriteScreenX;
    drawEndX   =  spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0)
      drawStartX = 0;
    if (drawEndX >= WIDTH)
      drawEndX = WIDTH - 1;

    for (stripe = drawStartX; stripe < drawEndX; ++stripe){
      texX = (int) (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXTURE_WIDTH / spriteWidth) / 256;

      if (transformY > 0 && stripe > 0 && stripe < WIDTH && transformY < ZBuffer[stripe])
      for (y = drawStartY; y < drawEndY; y++){
	a = y * 256 - h * 128 + spriteHeight * 128;
	texY = ((a * TEXTURE_HEIGHT) / spriteHeight) / 256;

        if (gos->gos[spriteOrder[i]].type == 0)
	  color = sfImage_getPixel(vars->textures->sprites->gameObjects[gos->gos[spriteOrder[i]].texture], texX, texY);
	else if (gos->gos[spriteOrder[i]].type == 1)
	  color = sfImage_getPixel(vars->textures->sprites->guard[gos->gos[spriteOrder[i]].texture], texX, texY);

	if (color.a > 0)
	  my_put_pixel(vars->framebuffer, stripe, y, color);
      }
    }
  }
}