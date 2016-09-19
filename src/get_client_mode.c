/*
** get_client_mode.c for CLIENT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Thu May  5 11:00:10 2016 Victor Gouet
** Last update Fri May 13 21:19:26 2016 Victor Gouet
*/

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "../include/myftp.h"

void			client_ip_to_server(t_client *client)
{
  int			i;

  if ((client->pasvIp = strdup(client->ip)) == NULL)
    return ;
  i = 0;
  while (client->pasvIp[i] != '\0')
    {
      if (client->pasvIp[i] == '.')
	client->pasvIp[i] = ',';
      ++i;
    }
}

t_client	*get_client_from_mode(t_command *command)
{
  t_client	*client;

  client = NULL;
  if (command->server_type == PASV)
    {
      client = get_client_from_server(command->pasv_server_fd);
    }
  if (command->server_type == PORT)
    {
      client = connect_to_socket(command->pasv_server_fd,
				 command->ip_active,
				 command->port_active);
    }
  return (client);
}
