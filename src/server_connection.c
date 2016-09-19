/*
** server_connection.c for SERVER CONNECTIONS in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 10:28:31 2016 Victor Gouet
** Last update Fri May 13 15:05:00 2016 Victor Gouet
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "../include/myftp.h"

int			get_fd_with_protocol_name(char const *protocole_name)
{
  struct protoent	*pe;

  if ((pe = getprotobyname(protocole_name)) == NULL)
    {
      write(2, "getprocolbyname failed !\n", 25);
      return (-1);
    }
  return (socket(AF_INET, SOCK_STREAM, pe->p_proto));
}

void			close_socket_fd(int const fd)
{
  if (close(fd) == -1)
    {
      write(2, "close has failed\n", 17);
    }
}

int			bind_socketaddr(int const fd, int const port)
{
  struct sockaddr_in	s_in;
  int			reuse;

  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  reuse = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
		 (const char*)&reuse, sizeof(reuse)) < 0)
    {
      perror("setsockopt(SO_REUSEADDR) failed");
      return (-1);
    }
  return (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)));
}

int			create_queue(int const fd, int const size)
{
  return (listen(fd, size));
}

t_client		*connect_to_socket(int const fd, char const *ip,
					   int const port)
{
  struct sockaddr_in	s_in;
  t_client		*client;

  if ((client = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = inet_addr(ip);
  if ((connect(fd, (struct sockaddr *)&s_in,
	       sizeof(s_in))) == -1)
    return (free(client), NULL);
  client->fd = fd;
  client->ip = strdup(ip);
  client_ip_to_server(client);
  return (client);
}
