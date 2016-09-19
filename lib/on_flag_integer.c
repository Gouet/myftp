/*
** on_flag_integer.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:37:58 2016 Victor Gouet
** Last update Wed Feb 10 10:41:50 2016 Victor Gouet
*/

#include <stdio.h>
#include <limits.h>
#include "storage.h"

int	numPlaces(int n)
{
  int	r;

  r = 1;
  if (n < 0)
    {
      n = (n == INT_MIN) ? INT_MAX : -n;
      ++r;
    }
  while (n > 9)
    {
      n /= 10;
      ++r;
    }
  return (r);
}

void	caracPlaces(int n, int *i, char *str)
{
  if (n == 0)
    return ;
  caracPlaces(n / 10, i, str);
  str[(*i)++] = (n % 10) + '0';
}

int	on_size_integer(va_list ap)
{
  int	nb;

  nb = va_arg(ap, int);
  return (numPlaces(nb));
}

void	on_storage_integer(va_list ap, char *ptr, int *i)
{
  int	score;
  int	tmp;

  score = va_arg(ap, int);
  tmp = score;
    if (score < 0)
      {
	ptr[(*i)++] = '-';
	if (score == -2147483648)
	  score = score * (-1) - 1;
	else
	  score = score * (-1);
      }
    if (score != 0)
      {
        caracPlaces(score, i, ptr);
        if (tmp == -2147483648)
	  ptr[(*i) - 1] += 1;
        return ;
      }
    ptr[(*i)++] = '0';
}
