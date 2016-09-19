/*
** passiv_exec.c for PASSIV EXEC in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Wed May  4 10:50:08 2016 Victor Gouet
** Last update Sat May 14 11:32:35 2016 Victor Gouet
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myftp.h"
#include "../lib/storage.h"

int		passiv_list(t_client *client, char **tab,
			    t_command *command)
{
  char		*str;
  t_client	*new_client;

  if ((new_client = get_client_from_mode(command)) == NULL)
    {
      command->server_type = UNKNOWN;
      command->pasv_server_fd = -1;
      return (send_msg_to_client(client, "450 failed connect.\r\n"), 0);
    }
  send_msg_to_client(client, "150 Here comes the directory listing.\r\n");
  command->server_type = UNKNOWN;
  if ((str = STRING("%s %s", "ls -ln", tab[1])) == NULL)
    return (send_msg_to_client(client, "450 Directory send Failed.\r\n"), 0);
  send_command_to_client(str, new_client);
  free(str);
  if (close(new_client->fd) == -1 || (command->pasv_server_fd != new_client->fd
				      && close(command->pasv_server_fd) == -1))
    send_msg_to_client(client, "450 Directory send Failed.\r\n");
  else
    send_msg_to_client(client, "226 Directory send OK.\r\n");
  free(new_client);
  command->pasv_server_fd = -1;
  return (0);
}

static int	send_msg_download(t_client *client, char **tab, int size)
{
  char		*str;

  send_msg_to_client(client, "150 Opening BINARY mode data connection for ");
  send_msg_to_client(client, tab[1]);
  send_msg_to_client(client, " (");
  if ((str = STRING("%d bytes).\r\n", size)) == NULL)
    return (0);
  send_msg_to_client(client, str);
  free(str);
  return (0);
}

int		passiv_download(t_client *client, char **tab,
				t_command *command)
{
  t_client	*new_client;
  int		size;

  if ((new_client = get_client_from_mode(command)) == NULL)
    {
      command->server_type = UNKNOWN;
      command->pasv_server_fd = -1;
      return (send_msg_to_client(client, "550 Failed to connect.\r\n"), 0);
    }
  command->server_type = UNKNOWN;
  if ((size = send_file_to_client(new_client, tab[1])) == -1)
    {
      send_msg_to_client(client, "550 Failed to open file.\r\n");
      delete_client(new_client);
      command->pasv_server_fd = -1;
      return (0);
    }
  send_msg_download(client, tab, size);
  if (close(new_client->fd) == -1 || (command->pasv_server_fd != new_client->fd
				      && close(command->pasv_server_fd) == -1))
    send_msg_to_client(client, "450 Transfer Failed.\r\n");
  else
    send_msg_to_client(client, "226 Transfer complete.\r\n");
  command->pasv_server_fd = -1;
  return (free(new_client), 0);
}

static int	passiv_upload_create_file(t_client *client, char *file)
{
  int		fd;
  char		buffer[4096 + 1];
  int		re;

  if ((fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0666)) == -1)
    return (-1);
  while ((re = read(client->fd, buffer, 4096)) > 0)
    {
      buffer[re] = '\0';
      if (write(fd, buffer, strlen(buffer)) == -1)
	return (-1);
    }
  if (close(fd) == -1)
    return (-1);
  return (0);
}

int		passiv_upload(t_client *client, char **tab,
			      t_command *command)
{
  t_client	*new_client;

  if ((new_client = get_client_from_mode(command)) == NULL)
    {
      command->server_type = UNKNOWN;
      command->pasv_server_fd = -1;
      return (send_msg_to_client(client, "550 Failed to connect.\r\n"), 0);
    }
  send_msg_to_client(client, "150 Opening ASCII mode data connection for ");
  send_msg_to_client(client, tab[1]);
  send_msg_to_client(client, "\r\n");
  command->server_type = UNKNOWN;
  if (passiv_upload_create_file(new_client, tab[1]) == -1)
    {
      send_msg_to_client(client, "550 Failed to create file.\r\n");
      command->pasv_server_fd = -1;
      return (delete_client(new_client), 0);
    }
  if (close(new_client->fd) == -1 || (command->pasv_server_fd != new_client->fd
				      && close(command->pasv_server_fd) == -1))
    send_msg_to_client(client, "450 Transfer Failed.\r\n");
  else
    send_msg_to_client(client, "226 Transfer complete.\r\n");
  command->pasv_server_fd = -1;
  return (free(new_client), 0);
}
