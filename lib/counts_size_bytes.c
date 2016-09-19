/*
** counts_size_bytes.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:36:42 2016 Victor Gouet
** Last update Wed Feb 10 10:37:00 2016 Victor Gouet
*/

#include <stdio.h>
#include "storage.h"

int		counts_size_bytes(char *format, va_list ap)
{
  int		i;
  int		size;

  i = 0;
  size = 0;
  while (format[i] != '\0')
    {
      if (format[i] == '%' && format[i + 1] != '\0')
        {
	  size += controller_flags_size(format[i + 1], ap);
	  ++i;
        }
        else
	  ++size;
        ++i;
    }
  return (size);
}
