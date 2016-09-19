/*
** on_flag_strings.c for size in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:30:32 2016 Victor Gouet
** Last update Wed Feb 10 10:30:57 2016 Victor Gouet
*/

#include <stdio.h>
#include "storage.h"

int	on_size_strings(va_list ap)
{
  char	*str;
  int	i;

  i = 0;
  if ((str = va_arg(ap, char *)) == NULL)
    return (0);
  while (str[i] != '\0')
    {
      ++i;
    }
  return (i);
}

void	on_storage_strings(va_list ap, char *ptr, int *i)
{
  char	*str;

  if ((str = va_arg(ap, char *)) == NULL)
    return ;
  while (*str != '\0')
    {
      ptr[(*i)++] = *(str++);
    }
}
