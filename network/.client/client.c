/*
** main.c for sfml in /home/benito/Misc/SFML
** 
** Made by Benoit Lormeau
** Login   <benoit.lormeau@epitech.net>
** 
** Started on  Sun Nov 27 17:40:35 2016 Benoit Lormeau
** Last update Sat Dec 31 20:16:14 2016 Benoit Lormeau
*/

#include "my_sfml.h"

void	error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

int		 main(void)
{
  sfTcpSocket	 *socket;
  sfPacket	 *sendPacket;
  sfPacket	 *receivePacket;
  sfIpAddress	  server;
  char		  ip[16] = "10.19.252.252";
  char		  username[32];
  bool		  done = false;

  socket = sfTcpSocket_create();
  server = sfIpAddress_fromString(ip);
  sendPacket = sfPacket_create();

  if (sfTcpSocket_connect(socket, server, 8080, (sfTime){60000000}) != sfSocketDone)
    error("Couldn't connect to server.");
  printf("Connected to %s:%hu\n", ip, 8080);

  if (sfTcpSocket_receivePacket(socket, sendPacket) != sfSocketDone)
    error("Couldn't receive identification packet.");
  if (sfPacket_readInt8(packet) == -1)
    error("Room is full. Exiting...");
  sfTcpSocket_setBlocking(socket, sfFalse);
  sfPacket_clear(sendPacket);

  receivePacket = sfPacket_create();

  char data[64];
  char msg[64];
  while (!done)
  {
    if (sfKeyboard_isKeyPressed(sfKeyReturn)){
      sfPacket_writeString(sendPacket, username);
      sfPacket_writeString(sendPacket, "r");
      sfPacket_writeFloat(sendPacket, 0.12);
      if (sfTcpSocket_sendPacket(socket, sendPacket) != sfSocketDone)
        error("send error.");
      else
        sfPacket_clear(sendPacket);
    }

    if (sfTcpSocket_receivePacket(socket, receivePacket) == sfSocketDone){
      sfPacket_readString(receivePacket, data);
      sfPacket_clear(receivePacket);
      printf("received: [%s]\n", data);
    }
  }

  return (0);
}