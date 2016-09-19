/*
** on_flag_bounded.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:37:10 2016 Victor Gouet
** Last update Wed Feb 10 10:37:48 2016 Victor Gouet
*/

#include <stdio.h>
#include "storage.h"

int		on_size_bounded(va_list ap)
{
  t_nstr	nstr;

  nstr = va_arg(ap, t_nstr);
  return (nstr.n);
}

void		on_storage_bounded(va_list ap, char *ptr, int *i)
{
  t_nstr	nstr;
  int		acr;

  acr = 0;
  nstr = va_arg(ap, t_nstr);
  if (nstr.str == NULL)
    return ;
  while (nstr.n > 0 && nstr.str[acr] != '\0')
    {
      ptr[(*i)++] = nstr.str[acr++];
      --(nstr.n);
    }
}
