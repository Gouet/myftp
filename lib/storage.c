/*
** storage.c for storage in /home/gouet_v/Lib/STRING
**
** Made by Victor Gouet
** Login   <gouet_v@epitech.net>
**
** Started on  Wed Feb 10 10:29:30 2016 Victor Gouet
** Last update Wed Feb 10 10:30:11 2016 Victor Gouet
*/

#include "storage.h"

char	*on_storage(char *format, va_list ap, char *str)
{
  int	i;

  i = 0;
  while (*format != '\0')
    {
      if (*format == '%' && *(format + 1) != '\0')
        {
	  controller_flags_storage(str, ap, &i, *(format + 1));
	  format += 2;
        }
      else
	str[i++] = *(format++);
    }
  str[i] = '\0';
  va_end(ap);
  return (str);
}

char		*get_string(char *format, ...)
{
  char		*str;
  va_list	ap;
  int		size;

  va_start(ap, format);
  size = counts_size_bytes(format, ap);
  if ((str = malloc(size + 1)) == NULL)
    return (NULL);
  va_end(ap);
  va_start(ap, format);
  return (on_storage(format, ap, str));
}
