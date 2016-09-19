/*
** init_command.c for COMMAND INIT in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May  3 14:45:27 2016 Victor Gouet
** Last update Fri May 13 15:31:12 2016 Victor Gouet
*/

#include <stdlib.h>
#include "../include/myftp.h"

void		init_command(t_command *command)
{
  command->mode = Unknown;
  command->pasv_server_fd = -1;
  command->server_type = UNKNOWN;
  command->port_active = -1;
  command->ip_active = NULL;
  command->login = NULL;
  if ((command->home_path = malloc(1024)) == NULL ||
      (command->path = malloc(1024)) == NULL)
    return ;
  if (getcwd(command->home_path, 1024) == NULL ||
      getcwd(command->path, 1024) == NULL)
    return ;
}

void		init_string(char *command[COMMAND_NUMBER])
{
  command[0] = "USER";
  command[1] = "PASS";
  command[2] = "CWD";
  command[3] = "CDUP";
  command[4] = "QUIT";
  command[5] = "DELE";
  command[6] = "PWD";
  command[7] = "PASV";
  command[8] = "PORT";
  command[9] = "HELP";
  command[10] = "NOOP";
  command[11] = "RETR";
  command[12] = "STOR";
  command[13] = "LIST";
}

void		init_fptr(int (*fptr[COMMAND_NUMBER])(t_client *,
						      char **,
						      t_command *))
{
  fptr[0] = on_user;
  fptr[1] = on_pass;
  fptr[2] = on_cwd;
  fptr[3] = on_cdup;
  fptr[4] = on_quit;
  fptr[5] = on_dele;
  fptr[6] = on_pwd;
  fptr[7] = on_pasv;
  fptr[8] = on_port;
  fptr[9] = on_help;
  fptr[10] = on_noop;
  fptr[11] = on_retr;
  fptr[12] = on_stor;
  fptr[13] = on_list;
}
