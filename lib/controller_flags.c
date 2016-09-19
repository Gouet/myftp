/*
** controller_flags.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:41:08 2016 Victor Gouet
** Last update Wed Feb 10 10:48:43 2016 Victor Gouet
*/

#include <stdio.h>
#include "storage.h"

static void	initialise_fptr_storage(void (*fptr[FLAGSNBR])(va_list,
							       char *, int *))
{
  fptr[0] = on_storage_strings;
  fptr[1] = on_storage_integer;
  fptr[2] = on_storage_bits_integer;
  fptr[3] = on_storage_bits_char;
  fptr[4] = on_storage_char;
  fptr[5] = on_storage_less;
  fptr[6] = on_storage_reverse;
  fptr[7] = on_storage_bounded;
}

static void	initialise_fptr_size(int (*fptr[FLAGSNBR])(va_list))
{
  fptr[0] = on_size_strings;
  fptr[1] = on_size_integer;
  fptr[2] = on_size_bits_integer;
  fptr[3] = on_size_bits_char;
  fptr[4] = on_size_char;
  fptr[5] = on_size_less;
  fptr[6] = on_size_reverse;
  fptr[7] = on_size_bounded;
}

int		controller_flags_size(char c, va_list ap)
{
  int		(*fptr[FLAGSNBR])(va_list);
  int		i;
  char		*flags;

  i = 0;
  flags = FLAGSCHAR;
  initialise_fptr_size(fptr);
  while (i < FLAGSNBR)
    {
      if (flags[i] == c)
        {
	  return (fptr[i](ap));
        }
      ++i;
    }
  return (2);
}

void		controller_flags_storage(char *str, va_list ap, int *i, char c)
{
  void		(*fptr[FLAGSNBR])(va_list, char *, int *);
  int		a;
  char		*flags;

  a = 0;
  flags = FLAGSCHAR;
  initialise_fptr_storage(fptr);
  while (a < FLAGSNBR)
    {
      if (flags[a] == c)
        {
	  fptr[a](ap, str, i);
	  return ;
        }
      ++a;
    }
  str[(*i)++] = '%';
  if (c != '%')
    str[(*i)++] = c;
}
