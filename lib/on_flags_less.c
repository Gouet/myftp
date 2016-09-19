/*
** on_flags_less.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:40:24 2016 Victor Gouet
** Last update Wed Feb 10 10:40:43 2016 Victor Gouet
*/

#include <stdio.h>
#include "storage.h"

int	on_size_less(va_list ap)
{
  return (va_arg(ap, int) * 0);
}

void	on_storage_less(va_list ap, char *ptr, int *i)
{
  int	value;

  value = va_arg(ap, int);
  while (*i >= 0 && value > 0)
    {
      ptr[(*i)--] = '\0';
      --value;
    }
  if ((*i) < 0)
    *i = 0;
}
