/*
** client_connection.c for CLIENT CONNECTION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 11:15:59 2016 Victor Gouet
** Last update Sat May 14 14:26:42 2016 Victor Gouet
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myftp.h"

t_client		*get_client_from_server(int const fd_server)
{
  t_client		*client;
  socklen_t		s_in_size;

  if ((client = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  s_in_size = sizeof(client->s_in_client);
  if ((client->fd = accept(fd_server,
			   (struct sockaddr *)&(client->s_in_client),
			   &s_in_size)) == -1)
    {
      free(client);
      return (NULL);
    }
  client->ip = inet_ntoa(client->s_in_client.sin_addr);
  client_ip_to_server(client);
  return (client);
}

int			send_file_to_client(t_client const *client,
					    char const *file)
{
  int			fd;
  int			re;
  char			buffer[4096 + 1];
  int			size;

  size = 0;
  if (access(file, R_OK) == -1)
    return (-1);
  if ((fd = open(file, O_RDONLY)) == -1)
    return (-1);
  while ((re = read(fd, buffer, 4096)) > 0)
    {
      buffer[re] = '\0';
      send_msg_to_client(client, buffer);
      size = size + re;
    }
  close(fd);
  return (size);
}

void			delete_client(t_client *client)
{
  if (close(client->fd) == -1)
    {
      write(2, "client close failed\n", 20);
    }
  free(client);
}

int			send_msg_to_client(t_client const *client,
					   char const *msg)
{
  return (write(client->fd, msg, strlen(msg)));
}

char		*recv_msg_from_client(t_client const *client)
{
  int		re;
  char		*buffer;
  char		str[4097];
  int		size;
  int		i;

  if ((buffer = malloc(4097)) == NULL)
    return (NULL);
  size = 0;
  while ((re = read(client->fd, str, 1)) > 0)
    {
      str[re] = '\0';
      i = 0;
      while (str[i] != '\0')
	{
	  buffer[size++] = str[i] == '\n' ? '\0' : str[i];
	  ++i;
	  if ((size >= 2 && buffer[size - 1] == '\0' &&
	      buffer[size - 2] == '\r') || size >= 4097)
	    return (buffer);
	}
    }
  free(buffer);
  return (NULL);
}
