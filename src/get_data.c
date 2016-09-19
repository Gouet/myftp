/*
** get_data.c for GESTION in /home/gouet_v/Rendu/semester4/PSU/PSU_2015_myftp
** 
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
** 
** Started on  Mon May  2 18:48:58 2016 Victor Gouet
** Last update Thu May 12 19:12:43 2016 Victor Gouet
*/

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/myftp.h"

static char		*acr_if_white_space(char *buffer, int *x,
					    size_t *y, char **tab)
{
  while ((*buffer == ' ' || *buffer == '\t') && *buffer != 0)
    {
      if (*x != 0)
	tab[(*y)++][*x] = 0;
      *x = 0;
      ++buffer;
    }
  if (*buffer == 0 || *buffer == '\r')
    {
      *x = 0;
      return (NULL);
    }
  return (buffer);
}

static char		**str_to_word_tab(char *buffer)
{
  char			**tab;
  size_t		y;
  int			x;
  char			*ref;

  ref = buffer;
  if ((tab = malloc((strlen(buffer) + 1) * sizeof(char *))) == NULL)
    return (NULL);
  y = 0;
  x = 0;
  while (*buffer != 0 && *buffer != '\r')
    {
      if ((buffer = acr_if_white_space(buffer, &x, &y, tab)) == NULL)
	break;
      if (x == 0 && (tab[y] = malloc(strlen(buffer) + 1)) == NULL)
	return (NULL);
      tab[y][x++] = *buffer;
      ++buffer;
    }
  if (x != 0)
    tab[y++][x] = 0;
  while (y < strlen(ref) + 1)
    tab[y++] = NULL;
  return (tab);
}

char		**split(char *str, char carac)
{
  char		**tab;
  int		x;
  int		y;

  x = 0;
  if (y = 0, (tab = malloc((strlen(str) + 1) * sizeof(char *))) == NULL)
    return (NULL);
  while (*str != 0)
    {
      if (x == 0)
	if ((tab[y] = malloc((strlen(str) + 1))) == NULL)
	  return (NULL);
      if (*str == carac)
	{
	  tab[y++][x] = '\0';
	  x = 0;
	}
      else
	tab[y][x++] = *str;
      ++str;
    }
  if (x != 0)
    tab[y++][x] = '\0';
  tab[y] = NULL;
  return (tab);
}

int		gestion_buffer(char *buffer, t_client *client,
			       t_command *protocole)
{
  char		**tab;
  char		*command[COMMAND_NUMBER];
  int		(*fptr[COMMAND_NUMBER])(t_client *, char **, t_command *);
  int		y;
  int		value;

  if ((tab = str_to_word_tab(buffer)) == NULL)
    return (-1);
  init_string(command);
  init_fptr(fptr);
  y = -1;
  value = 2;
  while (++y < COMMAND_NUMBER)
    {
      if (tab[0] != NULL && strcasecmp(tab[0], command[y]) == 0)
	value = fptr[y](client, tab, protocole);
    }
  if (value == 2)
    send_msg_to_client(client, "500 Unknown command.\r\n");
  y = -1;
  while (++y < (int)strlen(buffer) + 1)
    if (tab[y])
      free(tab[y]);
  free(tab);
  return (value);
}
