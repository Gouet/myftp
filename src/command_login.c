/*
** command_login.c for LOGIN in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 21:42:23 2016 Victor Gouet
** Last update Sat May 14 12:21:21 2016 Victor Gouet
*/

#include <stdlib.h>
#include <string.h>
#include "../include/myftp.h"

int	on_user(t_client *client, char **tab, t_command *command)
{
  if (command->mode == Login)
    {
      send_msg_to_client(client,
			 "530 Can t change the user.\r\n");
      return (0);
    }
  if (tab[1] == NULL)
    {
      send_msg_to_client(client, "530 needs login\r\n");
      return (0);
    }
  command->mode = LoginWithoutPass;
  command->login = strdup(tab[1]);
  send_msg_to_client(client, "331 Please specify the password.\r\n");
  return (0);
}

int	on_pass(t_client *client, char **tab, t_command *command)
{
  if (command->mode == Login)
    return (send_msg_to_client(client, "230 already log\r\n"), 0);
  if (command->mode != LoginWithoutPass && command->mode != Login)
    {
      send_msg_to_client(client, "503 login please\r\n");
      return (0);
    }
  if ((tab[1] == NULL && command->login &&
       strcmp(command->login, "Anonymous") == 0)
      || command->mode == Login)
    {
      send_msg_to_client(client, "230 passsword success\r\n");
      command->mode = Login;
      return (0);
    }
  command->mode = Unknown;
  send_msg_to_client(client, "530 wrong password or login\r\n");
  return (0);
}

int	on_cwd(t_client *client, char **tab, t_command *command)
{
  if (command->mode != Login)
    return (send_msg_to_client(client, "530 need login\r\n"), 0);
  if (tab[1] == NULL)
    return (send_msg_to_client(client, "501 need path\r\n"), 0);
  if (chdir(tab[1]) == -1)
    return (send_msg_to_client(client, "550 wrong path\r\n"), 0);
  free(command->path);
  command->path = NULL;
  if ((command->path = malloc(1024)) == NULL)
    return (send_msg_to_client(client, "550 malloc failed\r\n"), -1);
  if (getcwd(command->path, 1024) == NULL)
    return (send_msg_to_client(client, "550 malloc failed\r\n"), -1);
  if (strlen(command->home_path) > strlen(command->path))
    {
      chdir(command->home_path);
      free(command->path);
      if ((command->path = malloc(1024)) == NULL)
	return (send_msg_to_client(client, "550 malloc\r\n"), -1);
      if (getcwd(command->path, 1024) == NULL)
	return (send_msg_to_client(client, "550 malloc\r\n"), -1);
    }
  return (send_msg_to_client(client, "250 change ok\r\n"), 0);
}

int	on_cdup(t_client *client, char **tab, t_command *command)
{
  (void)tab;
  if (command->mode != Login)
    {
      send_msg_to_client(client, "530 need login\r\n");
      return (0);
    }
  if (strcmp(command->home_path, command->path) == 0
      || chdir("..") == -1)
    {
      send_msg_to_client(client, "250 sucess\r\n");
      return (0);
    }
  free(command->path);
  command->path = NULL;
  if ((command->path = malloc(1024 + 1)) == NULL)
    return (send_msg_to_client(client, "550 failed\r\n"), -1);
  if (getcwd(command->path, 1024) == NULL)
    return (send_msg_to_client(client, "550 failed\r\n"), -1);
  send_msg_to_client(client, "200 sucess\r\n");
  return (0);
}

int	on_quit(t_client *client, char **tab, t_command *command)
{
  (void)tab;
  send_msg_to_client(client, "221 Goodbye.\r\n");
  command->mode = Logout;
  return (-1);
}
