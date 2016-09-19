/*
** main.c for MAIN in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 10:13:21 2016 Victor Gouet
** Last update Mon May  2 22:56:54 2016 Victor Gouet
*/

#include <stdlib.h>
#include "../include/myftp.h"

void	run_ftp(int const port, char const *path)
{
  int	server_fd;

  if ((server_fd = create_server(port)) == -1)
    {
      write(2, "create_server failed\n", 21);
      return ;
    }
  run_server(server_fd, path);
}

int	main(int ac, char **av)
{
  if (ac != 3)
    {
      write(2, "Usage : ./server port path\n", 27);
      return (0);
    }
  run_ftp(atoi(av[1]), av[2]);
  return (0);
}
