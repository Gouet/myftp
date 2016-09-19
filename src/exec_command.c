/*
** exec_command.c for GET in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Tue May  3 17:57:24 2016 Victor Gouet
** Last update Tue May  3 18:55:42 2016 Victor Gouet
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../include/myftp.h"

int	        send_command_to_client(char *command, t_client *client)
{
  pid_t		cpid;
  int		status;

  status = 1;
  if ((cpid = fork()) == -1)
    return (1);
  if (cpid == 0)
    {
      if (dup2(client->fd, 1) == -1)
	exit(1);
      if (execl("/bin/sh", "/bin/sh", "-c", command, NULL) == -1)
	exit(1);
      delete_client(client);
      exit(1);
    }
  else
    {
      wait(&status);
    }
  return (status);
}
