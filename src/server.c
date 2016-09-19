/*
** server.c for server in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 12:04:28 2016 Victor Gouet
** Last update Thu May 12 21:13:09 2016 Victor Gouet
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../include/myftp.h"

int		create_server(int const port)
{
  int		server_fd;

  if ((server_fd = get_fd_with_protocol_name("TCP")) == -1)
    {
      write(2, "get_fd_with_protocol_name failed\n", 33);
      return (-1);
    }
  if (bind_socketaddr(server_fd, port) == -1)
    {
      write(2, "bind_socketaddr failed\n", 23);
      return (close_socket_fd(server_fd), -1);
    }
  if (create_queue(server_fd, SOMAXCONN) == -1)
    {
      write(2, "create_queue failed\n", 20);
      return (close_socket_fd(server_fd), -1);
    }
  return (server_fd);
}

void		on_client_gestion(t_client *client,
				  char const *path)
{
  char		*buffer;
  t_command	command;

  (void)path;
  send_msg_to_client(client, "220 Welcome !\r\n");
  init_command(&command);
  while ((buffer = recv_msg_from_client(client)))
    {
      if (gestion_buffer(buffer, client, &command) == -1)
	{
	  free(buffer);
	  break;
	}
      free(buffer);
    }
  if (command.path)
    free(command.path);
}

static int		add_new_client(t_list *list,
				       t_client *client,
				       pid_t pid)
{
  t_elem		*elem;

  if ((elem = malloc(sizeof(t_elem))) == NULL)
    return (-1);
  elem->next = NULL;
  elem->client = client;
  elem->pid = pid;
  if (list->begin == NULL && list->end == NULL)
    {
      list->begin = elem;
    }
  else
    {
      list->end->next = elem;
    }
  list->end = elem;
  return (0);
}

static int	kill_zombies(t_list *list)
{
  t_elem	*elem;
  int		status;

  elem = list->begin;
  while (elem != NULL)
    {
      waitpid(elem->pid, &status, WNOHANG);
      elem = elem->next;
    }
  return (0);
}

int		run_server(int const server, char const *path)
{
  t_client	*client;
  pid_t		pid;
  t_list	list;

  if (list.end = NULL, list.begin = NULL, chdir(path) == -1)
    return (write(2, "Wrong path\n", 11), -1);
  while (42)
    {
      if ((client = get_client_from_server(server)) == NULL)
	return (close_socket_fd(server), -1);
      kill_zombies(&list);
      if ((pid = fork()) == -1)
	return (close_socket_fd(server), -1);
      if (pid == 0)
	{
	  on_client_gestion(client, path);
	  delete_client(client);
	  exit(0);
	}
      else
	if (add_new_client(&list, NULL, pid) == -1)
	  return (0);
      delete_client(client);
    }
  return (close_socket_fd(server), 0);
}
