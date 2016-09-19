/*
** command_mode.c for GESTIOn in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May  3 12:19:30 2016 Victor Gouet
** Last update Sat May 14 13:47:26 2016 Victor Gouet
*/

#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../include/myftp.h"
#include "../lib/storage.h"

int	on_pasv(t_client *client, char **tab, t_command *command)
{
  int	port[2];
  char	buffer[4096];

  (void)tab;
  srand(time(NULL));
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  send_msg_to_client(client, "227 Entering Passive Mode (");
  send_msg_to_client(client, client->pasvIp);
  port[0] = 1 + (rand() % 255);
  port[1] = 1 + (rand() % 255);
  sprintf(buffer, ",%d,%d).\r\n", port[0], port[1]);
  if (command->pasv_server_fd != -1)
    close_socket_fd(command->pasv_server_fd);
  command->server_type = PASV;
  command->pasv_server_fd = create_server(256 * port[0] + port[1]);
  send_msg_to_client(client, buffer);
  return (0);
}

int	on_port(t_client *client, char **tab, t_command *command)
{
  char	**splited;
  char	*parenthesis;

  if (command->mode != Login)
    return (send_msg_to_client(client, "530 need login\r\n"), 0);
  if (tab[1] == NULL)
    return (send_msg_to_client(client, "503 need args\r\n"), 0);
  if ((splited = split(tab[1], ',')) == NULL || splited[0] == NULL
      || splited[1] == NULL || splited[2] == NULL || splited[3] == NULL
      || splited[4] == NULL || splited[5] == NULL)
    return (send_msg_to_client(client, "503 failed\r\n"), 0);
  if (command->ip_active)
    free(command->ip_active);
  parenthesis = strlen(splited[0]) > 1 ? &splited[0][1] : splited[0];
  command->ip_active = STRING("%s.%s.%s.%s", parenthesis,
			      splited[1], splited[2], splited[3]);
  command->port_active = 256 * atoi(splited[4]) + atoi(splited[5]);
  if (command->pasv_server_fd != -1)
    close_socket_fd(command->pasv_server_fd);
  command->server_type = PORT;
  if ((command->pasv_server_fd = get_fd_with_protocol_name("TCP")) == -1)
    return (send_msg_to_client(client, "503 failed\r\n"), 0);
  send_msg_to_client(client, "200 Entering Active Mode.\r\n");
  return (0);
}

int	on_help(t_client *client, char **tab, t_command *command)
{
  char	*newCommand[COMMAND_NUMBER];
  int	i;

  (void)tab;
  i = 0;
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  init_string(newCommand);
  send_msg_to_client(client,
		     "214-The following commands are recognized.\r\n");
  while (i < COMMAND_NUMBER)
    {
      send_msg_to_client(client, " ");
      send_msg_to_client(client, newCommand[i]);
      ++i;
    }
  send_msg_to_client(client, "\r\n214 Help Ok.\r\n");
  return (0);
}

int	on_noop(t_client *client, char **tab, t_command *command)
{
  (void)tab;
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  send_msg_to_client(client, "200 NOOP ok.\r\n");
  return (0);
}
