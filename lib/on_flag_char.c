/*
** on_flag_char.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:33:47 2016 Victor Gouet
** Last update Wed Feb 10 10:34:03 2016 Victor Gouet
*/

#include <stdio.h>
#include "storage.h"

int	on_size_char(va_list ap)
{
  va_arg(ap, int);
  return (1);
}

void	on_storage_char(va_list ap, char *ptr, int *i)
{
  char	str;

  str = (char)va_arg(ap, int);
  ptr[(*i)++] = str;
}
