/*
** main.c for sfml in /home/benito/Misc/SFML
**
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.net>
**
** Started on  Sun Nov 27 17:40:35 2016 Benoit Lormeau
** Last update Fri Oct  6 14:47:15 2017 Benoit Lormeau
*/

#include "my_sfml.h"

void	error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

bool	port_isValid(unsigned short port)
{
  if (port > 0 && port < 65535)
    return (true);
  return (false);
}

int		 main(void)
{
  sfTcpListener		*listener;
  sfSocketSelector	*selector;
  sfPacket		*packet,
			*broadcastPacket;
  t_clients		clients;
  t_player		players[8];
  sfSocketStatus	status;
  sfUint8		id;
  unsigned short	port;
  bool			done = false;
  char			mapPath[64];
  char			action[32];
  float			x, y;

  // CONFIG
  do {
    printf("Enter server port: ");
    scanf("%hu", &port);
  } while (!port_isValid(port));

  do {
    printf("Enter map name to use: ");
    scanf("%s", mapPath);
  } while (!strcmp(mapPath, ""));

  clients.count = 0;
  packet = sfPacket_create();
  broadcastPacket = sfPacket_create();

  // LISTENER SETUP
  listener = sfTcpListener_create();
  selector = sfSocketSelector_create();
  sfTcpListener_setBlocking(listener, sfFalse);

  do {
    status = sfTcpListener_listen(listener, port, sfIpAddress_Any);
  } while (status != sfSocketDone);

  // INFOS
  printf("\n========================\n");
  printf("Local address: %s\n", sfIpAddress_getLocalAddress().address);
  printf("Listening to port %hu\n", port);
  printf("Using map '%s'\n", mapPath);

  sfSocketSelector_addTcpListener(selector, listener);

  //  BOUCLE INFINIE  //
  while (!done)
  {
    /// Incoming Event
    if (sfSocketSelector_wait(selector, sfTime_Zero))
    {
      /* New Client */
      if (sfSocketSelector_isTcpListenerReady(selector, listener))
      {
        sfTcpSocket *client = sfTcpSocket_create();

        // If room ain't full
        if (clients.count < 8)
        {
          if (sfTcpListener_accept(listener, &client) == sfSocketDone){

            id = clients.count;
            sfPacket_writeInt8(packet, id);		// Send him his id
            sfPacket_writeString(packet, mapPath);	// And map path
            sfTcpSocket_sendPacket(client, packet);
            sfPacket_clear(packet);

            for (int i = 0; i < clients.count; ++i){
              sfPacket_writeInt8(packet, i);
              sfPacket_writeString(packet, "pos");
              sfPacket_writeFloat(packet, players[i].pos.x);
              sfPacket_writeFloat(packet, players[i].pos.y);
              sfTcpSocket_sendPacket(client, packet);
              sfPacket_clear(packet);

              sfPacket_writeInt8(packet, i);
              sfPacket_writeString(packet, "dir");
              sfPacket_writeFloat(packet, players[i].dir.x);
              sfPacket_writeFloat(packet, players[i].dir.y);
              sfTcpSocket_sendPacket(client, packet);
              sfPacket_clear(packet);
            }
          }

          clients.list[clients.count++] = client;
          sfSocketSelector_addTcpSocket(selector, client);
          printf("Client has connected to room (%d/8)\n", clients.count);
        }
        else {  // Room is full
          id = -1;
          sfPacket_writeInt8(packet, id);
          sfTcpSocket_sendPacket(client, packet);
          sfTcpSocket_disconnect(client);
          printf("Client tryed to connect but room is full.\n");
        }
      }
      else {  /* Socket Sending Data */
        for (int i = 0; i < clients.count; ++i)  // Check for all of them
        {
          if (sfSocketSelector_isTcpSocketReady(selector, clients.list[i]))
          {
            if (sfTcpSocket_receivePacket(clients.list[i], packet) == sfSocketDone)
            {
              broadcastPacket = sfPacket_copy(packet);
              id = sfPacket_readInt8(packet);
              sfPacket_readString(packet, action);
              x = sfPacket_readFloat(packet);
              y = sfPacket_readFloat(packet);

              if (!strcmp(action, "pos")){
                players[id].pos.x = x;
                players[id].pos.y = y;
              }
              else if (!strcmp(action, "dir")){
                players[id].dir.x = x;
                players[id].dir.y = y;
              }
              else if (!strcmp(action, "shot")){
                players[id].hp = 0;
              }
              else if (!strcmp(action, "res")){
                players[id].hp = 100;
              }

              for (int j = 0; j < clients.count; ++j){
                if (i != j)
                  sfTcpSocket_sendPacket(clients.list[j], broadcastPacket);
              }

              sfPacket_clear(packet);
            }
          }
        }
      }
    }
  }

  return (0);
}
