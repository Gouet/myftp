/*
** on_flags_bits.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:31:09 2016 Victor Gouet
** Last update Wed Feb 10 10:42:34 2016 Victor Gouet
*/

#include <stdio.h>
#include "storage.h"

int	on_size_bits_integer(va_list ap)
{
  va_arg(ap, int);
  return (32);
}

void		on_storage_bits_integer(va_list ap, char *ptr, int *i)
{
  t_integer	bits;
  int		acr;
  int		value;

  acr = 3;
  value = va_arg(ap, int);
  bits.value = value;
  while (acr >= 0)
    {
      ptr[(*i)] = bits.bits[acr].a + '0';
      ptr[(*i) + 1] = bits.bits[acr].b + '0';
      ptr[(*i) + 2] = bits.bits[acr].c + '0';
      ptr[(*i) + 3] = bits.bits[acr].d + '0';
      ptr[(*i) + 4] = bits.bits[acr].e + '0';
      ptr[(*i) + 5] = bits.bits[acr].f + '0';
      ptr[(*i) + 6] = bits.bits[acr].g + '0';
      ptr[(*i) + 7] = bits.bits[acr].h + '0';
      (*i) += 8;
      --acr;
    }
}

int	on_size_bits_char(va_list ap)
{
  va_arg(ap, int);
  return (8);
}

void		on_storage_bits_char(va_list ap, char *ptr, int *i)
{
  t_bits	*bits;
  char		value;

  value = (char)va_arg(ap, int);
  bits = (t_bits *)&value;
  ptr[(*i)] = bits->a + '0';
  ptr[(*i) + 1] = bits->b + '0';
  ptr[(*i) + 2] = bits->c + '0';
  ptr[(*i) + 3] = bits->d + '0';
  ptr[(*i) + 4] = bits->e + '0';
  ptr[(*i) + 5] = bits->f + '0';
  ptr[(*i) + 6] = bits->g + '0';
  ptr[(*i) + 7] = bits->h + '0';
  (*i) += 8;
}
