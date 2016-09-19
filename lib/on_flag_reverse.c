/*
** on_flag_reverse.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:39:21 2016 Victor Gouet
** Last update Wed Feb 10 10:40:16 2016 Victor Gouet
*/

#include <stdio.h>
#include "storage.h"

static int	reverse_str(char *str, char *rev)
{
  int		i;

  if (*str == '\0')
    return (0);
  i = reverse_str(str + 1, rev);
  rev[i] = *str;
  return (i + 1);
}

void		on_storage_reverse(va_list ap, char *ptr, int *i)
{
  char		*str;
  int		size;

  if ((str = va_arg(ap, char *)) == NULL)
    return ;
  size = 0;
  while (str[size] != '\0')
    ++size;
  reverse_str(str, &ptr[*i]);
  (*i) += size;
}

int		on_size_reverse(va_list ap)
{
  char		*str;
  int		i;

  if ((str = va_arg(ap, char *)) == NULL)
    return (0);
  i = 0;
  while (str[i] != '\0')
    ++i;
  return (i);
}
