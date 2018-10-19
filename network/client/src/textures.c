/*
** textures.c for wolf3d in /home/benito/delivery/wolf3d/bonus
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Thu Dec 15 19:07:36 2016 Benoit Lormeau
** Last update Thu Dec 15 19:07:45 2016 Benoit Lormeau
*/

#include "my.h"
#include "textures.h"
#include "wolf3d.h"

int	load_textures(t_vars *vars)
{
  vars->textures              = malloc(sizeof(t_textures));
  vars->textures->sprites     = malloc(sizeof(t_sprites *));
  vars->textures->walls       = malloc(sizeof(sfImage *) * 15);
  vars->textures->weapons     = malloc(sizeof(sfTexture **) * 4);

  vars->textures->sprites->gameObjects	= malloc(sizeof(sfImage *) * 3);
  vars->textures->sprites->guard	= malloc(sizeof(sfImage *) * 106);

  for (int i = 0; i < 4; ++i)
    vars->textures->weapons[i] = malloc(sizeof(sfTexture *) * 5);
  
  if (vars->textures		== NULL) return (0);
  if (vars->textures->sprites	== NULL) return (0);
  if (vars->textures->walls	== NULL) return (0);
  if (vars->textures->weapons	== NULL) return (0);

  vars->textures->walls[0]  = sfImage_createFromFile(WALL_UNDEF);
  vars->textures->walls[1]  = sfImage_createFromFile(WALL_A);
  vars->textures->walls[2]  = sfImage_createFromFile(WALL_B);
  vars->textures->walls[3]  = sfImage_createFromFile(WALL_C);
  vars->textures->walls[4]  = sfImage_createFromFile(WALL_D);
  vars->textures->walls[5]  = sfImage_createFromFile(WALL_E);
  vars->textures->walls[6]  = sfImage_createFromFile(WALL_F);
  vars->textures->walls[7]  = sfImage_createFromFile(WALL_G);
  vars->textures->walls[8]  = sfImage_createFromFile(WALL_H);
  vars->textures->walls[9]  = sfImage_createFromFile(WALL_I);
  vars->textures->walls[10] = sfImage_createFromFile(WALL_J);
  vars->textures->walls[11] = sfImage_createFromFile(WALL_K);
  vars->textures->walls[12] = sfImage_createFromFile(WALL_L);
  vars->textures->walls[13] = sfImage_createFromFile(WALL_M);
  vars->textures->walls[14] = sfImage_createFromFile(WALL_N);

  vars->textures->sprites->gameObjects[0] = sfImage_createFromFile(SPRITE_PILLAR);
  vars->textures->sprites->gameObjects[1] = sfImage_createFromFile(SPRITE_BARREL);
  vars->textures->sprites->gameObjects[2] = sfImage_createFromFile(SPRITE_LIGHT);

  vars->textures->sprites->guard[0]  = sfImage_createFromFile(GUARD_00);
  vars->textures->sprites->guard[1]  = sfImage_createFromFile(GUARD_01);
  vars->textures->sprites->guard[2]  = sfImage_createFromFile(GUARD_02);
  vars->textures->sprites->guard[3]  = sfImage_createFromFile(GUARD_03);
  vars->textures->sprites->guard[4]  = sfImage_createFromFile(GUARD_04);
  vars->textures->sprites->guard[5]  = sfImage_createFromFile(GUARD_05);
  vars->textures->sprites->guard[6]  = sfImage_createFromFile(GUARD_06);
  vars->textures->sprites->guard[7]  = sfImage_createFromFile(GUARD_07);
  vars->textures->sprites->guard[10] = sfImage_createFromFile(GUARD_10);
  vars->textures->sprites->guard[11] = sfImage_createFromFile(GUARD_11);
  vars->textures->sprites->guard[12] = sfImage_createFromFile(GUARD_12);
  vars->textures->sprites->guard[13] = sfImage_createFromFile(GUARD_13);
  vars->textures->sprites->guard[14] = sfImage_createFromFile(GUARD_14);
  vars->textures->sprites->guard[15] = sfImage_createFromFile(GUARD_15);
  vars->textures->sprites->guard[16] = sfImage_createFromFile(GUARD_16);
  vars->textures->sprites->guard[17] = sfImage_createFromFile(GUARD_17);
  vars->textures->sprites->guard[20] = sfImage_createFromFile(GUARD_20);
  vars->textures->sprites->guard[21] = sfImage_createFromFile(GUARD_21);
  vars->textures->sprites->guard[22] = sfImage_createFromFile(GUARD_22);
  vars->textures->sprites->guard[23] = sfImage_createFromFile(GUARD_23);
  vars->textures->sprites->guard[24] = sfImage_createFromFile(GUARD_24);
  vars->textures->sprites->guard[25] = sfImage_createFromFile(GUARD_25);
  vars->textures->sprites->guard[26] = sfImage_createFromFile(GUARD_26);
  vars->textures->sprites->guard[27] = sfImage_createFromFile(GUARD_27);
  vars->textures->sprites->guard[30] = sfImage_createFromFile(GUARD_30);
  vars->textures->sprites->guard[31] = sfImage_createFromFile(GUARD_31);
  vars->textures->sprites->guard[32] = sfImage_createFromFile(GUARD_32);
  vars->textures->sprites->guard[33] = sfImage_createFromFile(GUARD_33);
  vars->textures->sprites->guard[34] = sfImage_createFromFile(GUARD_34);
  vars->textures->sprites->guard[35] = sfImage_createFromFile(GUARD_35);
  vars->textures->sprites->guard[36] = sfImage_createFromFile(GUARD_36);
  vars->textures->sprites->guard[37] = sfImage_createFromFile(GUARD_37);
  vars->textures->sprites->guard[40] = sfImage_createFromFile(GUARD_40);
  vars->textures->sprites->guard[41] = sfImage_createFromFile(GUARD_41);
  vars->textures->sprites->guard[42] = sfImage_createFromFile(GUARD_42);
  vars->textures->sprites->guard[43] = sfImage_createFromFile(GUARD_43);
  vars->textures->sprites->guard[44] = sfImage_createFromFile(GUARD_44);
  vars->textures->sprites->guard[45] = sfImage_createFromFile(GUARD_45);
  vars->textures->sprites->guard[46] = sfImage_createFromFile(GUARD_46);
  vars->textures->sprites->guard[47] = sfImage_createFromFile(GUARD_47);
  vars->textures->sprites->guard[50] = sfImage_createFromFile(GUARD_50);
  vars->textures->sprites->guard[60] = sfImage_createFromFile(GUARD_60);
  vars->textures->sprites->guard[70] = sfImage_createFromFile(GUARD_70);
  vars->textures->sprites->guard[101] = sfImage_createFromFile(GUARD_100);
  vars->textures->sprites->guard[102] = sfImage_createFromFile(GUARD_200);
  vars->textures->sprites->guard[103] = sfImage_createFromFile(GUARD_300);
  vars->textures->sprites->guard[104] = sfImage_createFromFile(GUARD_400);
  vars->textures->sprites->guard[105] = sfImage_createFromFile(GUARD_500);

  vars->textures->weapons[0][0] = sfTexture_createFromFile(KNIFE_0, NULL);
  vars->textures->weapons[0][1] = sfTexture_createFromFile(KNIFE_1, NULL);
  vars->textures->weapons[0][2] = sfTexture_createFromFile(KNIFE_2, NULL);
  vars->textures->weapons[0][3] = sfTexture_createFromFile(KNIFE_3, NULL);
  vars->textures->weapons[0][4] = sfTexture_createFromFile(KNIFE_4, NULL);
  vars->textures->weapons[1][0] = sfTexture_createFromFile(GUN_0, NULL);
  vars->textures->weapons[1][1] = sfTexture_createFromFile(GUN_1, NULL);
  vars->textures->weapons[1][2] = sfTexture_createFromFile(GUN_2, NULL);
  vars->textures->weapons[1][3] = sfTexture_createFromFile(GUN_3, NULL);
  vars->textures->weapons[1][4] = sfTexture_createFromFile(GUN_4, NULL);
  vars->textures->weapons[2][0] = sfTexture_createFromFile(RIFLE_0, NULL);
  vars->textures->weapons[2][1] = sfTexture_createFromFile(RIFLE_1, NULL);
  vars->textures->weapons[2][2] = sfTexture_createFromFile(RIFLE_2, NULL);
  vars->textures->weapons[2][3] = sfTexture_createFromFile(RIFLE_3, NULL);
  vars->textures->weapons[2][4] = sfTexture_createFromFile(RIFLE_4, NULL);
  vars->textures->weapons[3][0] = sfTexture_createFromFile(GATLING_0, NULL);
  vars->textures->weapons[3][1] = sfTexture_createFromFile(GATLING_1, NULL);
  vars->textures->weapons[3][2] = sfTexture_createFromFile(GATLING_2, NULL);
  vars->textures->weapons[3][3] = sfTexture_createFromFile(GATLING_3, NULL);
  vars->textures->weapons[3][4] = sfTexture_createFromFile(GATLING_4, NULL);

  return (1);
}

int	get_wall_index(char c)
{
  char	wall_tab[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < 26; ++i){
    if (wall_tab[i] == c)
      return (i + 1);
  }

  return (0);
}

/*
** a: pillar
** b: barrel
** c: green light
*/
int	get_go_index(char c)
{
  char	go_tab[3] = "abc";

  for (int i = 0; i < 3; ++i){
    if (go_tab[i] == c)
      return (i);
  }

  return (0);
}

/*
** 0: guard
*/
int	get_ent_index(char c)
{
  char	ent_tab[1] = "0";

  for (int i = 0; i < 1; ++i){
    if (ent_tab[i] == c)
      return (i);
  }

  return (0);
}