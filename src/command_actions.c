/*
** command_actions.c for ACTIONS in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May  3 11:03:32 2016 Victor Gouet
** Last update Fri May 13 15:57:57 2016 Victor Gouet
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/myftp.h"

int		on_stor(t_client *client, char **tab, t_command *command)
{
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  if (command->server_type == UNKNOWN)
    {
      send_msg_to_client(client, "425 Use PORT or PASV first.\r\n");
      return (0);
    }
  if (tab[1] == NULL)
    {
      send_msg_to_client(client, "550 Failed to open file.\r\n");
      return (0);
    }
  passiv_upload(client, tab, command);
  return (0);
}

int		on_retr(t_client *client, char **tab, t_command *command)
{
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  if (command->server_type == UNKNOWN)
    {
      send_msg_to_client(client, "425 Use PORT or PASV first.\r\n");
      return (0);
    }
  if (tab[1] == NULL)
    {
      send_msg_to_client(client, "550 Failed to open file.\r\n");
      return (0);
    }
  passiv_download(client, tab, command);
  return (0);
}

int		on_list(t_client *client, char **tab, t_command *command)
{
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  if (command->server_type == UNKNOWN)
    {
      send_msg_to_client(client, "425 Use PORT or PASV first.\r\n");
      return (0);
    }
  passiv_list(client, tab, command);
  return (0);
}

int		on_dele(t_client *client, char **tab, t_command *command)
{
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  if (tab[1] == NULL)
    {
      send_msg_to_client(client, "550 need file\r\n");
      return (0);
    }
  if (remove(tab[1]) == -1)
    return (send_msg_to_client(client, "550 no file\r\n"), 0);
  send_msg_to_client(client, "250 delete Ok.\r\n");
  return (0);
}

int		on_pwd(t_client *client, char **tab, t_command *command)
{
  int		i;

  (void)tab;
  i = strlen(command->home_path);
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  send_msg_to_client(client, "257 \"");
  if (strlen(command->path) == strlen(command->home_path))
    send_msg_to_client(client, "/");
  else
    send_msg_to_client(client, &command->path[i]);
  send_msg_to_client(client, "\"\r\n");
  return (0);
}
