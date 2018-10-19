/*
** network.c for wolf3d in /home/benito/Misc/wolf3d-network/client
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.eu>
** 
** Started on  Fri Jan  6 12:36:27 2017 Benoit Lormeau
** Last update Fri Jan  6 12:38:36 2017 Benoit Lormeau
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "wolf3d.h"

void	error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

bool			ip_isValid(char *ip)
{
  struct sockaddr_in	sa;
  int			result;

  result = inet_pton(AF_INET, ip, &(sa.sin_addr));
  return (result != 0);
}

bool	port_isValid(unsigned short port)
{
  if (port > 0 && port < 65535)
    return (true);
  return (false);
}

void			sendPos(t_plyr *player, t_net *net)
{
  sfSocketStatus	status;

  sfPacket_writeInt8(net->packet, net->id);
  sfPacket_writeString(net->packet, "pos");
  sfPacket_writeFloat(net->packet, POS.x);
  sfPacket_writeFloat(net->packet, POS.y);
  status = sfTcpSocket_sendPacket(net->socket, net->packet);
  if (status != sfSocketDone)
    fprintf(stderr, "Could not send position. (%d)\n", status);
  sfPacket_clear(net->packet);
}

void			sendDir(t_plyr *player, t_net *net)
{
  sfSocketStatus	status;

  sfPacket_writeInt8(net->packet, net->id);
  sfPacket_writeString(net->packet, "dir");
  sfPacket_writeFloat(net->packet, DIR.x);
  sfPacket_writeFloat(net->packet, DIR.y);
  status = sfTcpSocket_sendPacket(net->socket, net->packet);
  if (status != sfSocketDone)
    fprintf(stderr, "Could not send direction. (%d)\n", status);
  sfPacket_clear(net->packet);
}

void			sendShot(short id, t_net *net)
{
  sfSocketStatus	status;

  sfPacket_writeInt8(net->packet, net->id);
  sfPacket_writeString(net->packet, "shot");
  sfPacket_writeInt16(net->packet, id);
  status = sfTcpSocket_sendPacket(net->socket, net->packet);
  if (status != sfSocketDone)
    fprintf(stderr, "Could not send shot. (%d)\n", status);
  sfPacket_clear(net->packet);
}

void			sendRes(t_net *net)
{
  sfSocketStatus	status;

  sfPacket_writeInt8(net->packet, net->id);
  sfPacket_writeString(net->packet, "res");
  sfPacket_writeInt8(net->packet, net->id);
  status = sfTcpSocket_sendPacket(net->socket, net->packet);
  if (status != sfSocketDone)
    fprintf(stderr, "Could not send respawn. (%d)\n", status);
  sfPacket_clear(net->packet);
}

void		update_ents(t_ents *ents, t_plyr *player, t_net *net)
{
  sfInt8	id;
  char		action[32];
  float		x, y;
  int		idx;

  id = sfPacket_readInt8(net->packet);
  sfPacket_readString(net->packet, action);
  idx = ents_findIndexById(ents, id);

  if (idx != -1)
  {
    if (!strcmp(action, "pos")){
      x = sfPacket_readFloat(net->packet);
      y = sfPacket_readFloat(net->packet);

      ents->ents[idx].pos.x = x;
      ents->ents[idx].pos.y = y;
    }
    else if (!strcmp(action, "dir")){
      x = sfPacket_readFloat(net->packet);
      y = sfPacket_readFloat(net->packet);

      ents->ents[idx].dir.x = x;
      ents->ents[idx].dir.y = y;
    }
    else if (!strcmp(action, "shot")){
      short targetID = sfPacket_readInt16(net->packet);

      if (targetID == net->id)
        player->hp = 0;
      else
        ents->ents[ents_findIndexById(ents, targetID)].hp = 0;
    }
    else if (!strcmp(action, "res")){
      short targetID = sfPacket_readInt8(net->packet);
      ents->ents[ents_findIndexById(ents, targetID)].hp = 100;
    }
  }

  sfPacket_clear(net->packet);
}